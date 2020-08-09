/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 18:11:10 by jle-corr          #+#    #+#             */
/*   Updated: 2020/08/09 03:09:08 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** map_measuring keep the lenght of the biggest line and count how
** many lines there is in the map. It also check if there is no empty line
** between and if the height of the map is over 2.
*/

int				map_measuring(t_cubfile *cbfile, t_gnl *gnl)
{
	int			len;

	while ((gnl->ret = get_next_line(gnl->fd, &(gnl->line))))
	{
		if (*(gnl->line) && (++(cbfile->d_map.h))
				&& (len = ft_strlen(gnl->line)))
			cbfile->d_map.w = ((len > cbfile->d_map.w) ?
					len : cbfile->d_map.w);
		else
		{
			if (cbfile->d_map.h == 0)
				(gnl->nwline)++;
			else
			{
				free(gnl->line);
				return (ft_error("map error, empty line between"));
			}
		}
		free(gnl->line);
	}
	if (gnl->ret == -1)
		return (ft_error("gnl error"));
	free(gnl->line);
	return ((cbfile->d_map.h < 3 ? 0 : 1));
}

/*
** map_cpy check if each character of the current line is
** authorized and copy it in the map line. It also check if there is a
** position character and if it is, if it's the first (it must be only
** one position character (N, S, E, W)). Then record the position.
** before quiting it checks if the last character is space, 1 or 2.
*/

double			char_to_angle(char c)
{
	if (c == 'S')
		return (270.0);
	else if (c == 'N')
		return (90.0);
	else if (c == 'E')
		return (0.0);
	else if (c == 'W')
		return (180.0);
	else
		return (-1.0);
}

int				map_cpy(t_cubfile *cbfile, char *line, int h)
{
	int			w;

	w = 0;
	while (*line)
	{
		if (*line == '0' || *line == '1' || *line == ' ' ||
				(*line == '2' && cbfile->sprite_nb++ > -1))
			cbfile->map[h][w] = *line;
		else if ((*line == 'N' || *line == 'E' || *line == 'W'
					|| *line == 'S') && cbfile->pos.x == -1)
		{
			cbfile->map[h][w] = *line;
			cbfile->pos.x = w + 0.532;
			cbfile->pos.y = h + 0.532;
			cbfile->pos.a = char_to_angle(*line);
		}
		else
			return (0);
		line++;
		w++;
	}
	if (*(line - 1) != '1' && *(line - 1) != ' ' && *(line - 1) != '2')
		return (0);
	return (1);
}

/*
** map_recording creates a new adress line of the maximum map size to
** each map board, full it with spaces. Then it get the next line of the map
** and check the first character which must be space 1 or 2.
** Then it copy the line in the map.
*/

int				map_recording(t_cubfile *c, t_gnl *g)
{
	int			i;

	i = -1;
	c->pos.x = -1;
	while (++i < c->d_map.h)
	{
		if (!(c->map[i] = ft_strnewspace(c->d_map.w)))
			return (0);
		if ((get_next_line(g->fd, &(g->line))) < 0)
			return (ft_freemap("gnl error", i, g->line, c));
		if (*(g->line) != ' ' && *(g->line) != '1' && *(g->line) != '2')
			return (ft_freemap("wrong char in start of map", i, g->line, c));
		if (!map_cpy(c, g->line, i))
			return (ft_freemap("wrong spawn, eol or char", i, g->line, c));
		free(g->line);
	}
	c->map[i] = NULL;
	if (c->pos.x == -1)
		return (ft_freemap("No player position in map", i - 1, NULL, c));
	return (1);
}

int				handle_map(t_cubfile *cbfile, t_gnl *gnl, char *file)
{
	int			i;

	cbfile->sprite_nb = 0;
	cbfile->d_map.w = 0;
	cbfile->d_map.h = 0;
	if (!map_measuring(cbfile, gnl))
		return (0);
	if (close(gnl->fd) == -1)
		return (ft_error("close error"));
	if (!(cbfile->map = (char**)malloc(sizeof(char*) * (cbfile->d_map.h + 1))))
		return (0);
	if ((gnl->fd = open(file, O_RDONLY)) < 0)
		return (0);
	i = 0;
	while (i++ < gnl->nwline)
	{
		if (!get_next_line(gnl->fd, &(gnl->line)))
			return (ft_error("gnl error"));
		free(gnl->line);
	}
	if (!map_recording(cbfile, gnl))
		return (0);
	return (1);
}

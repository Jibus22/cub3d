/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 18:11:10 by jle-corr          #+#    #+#             */
/*   Updated: 2020/04/29 19:51:43 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char			*ft_strnewpsace(int size)
{
	char		*new;

	if (!(new = (char*)malloc(sizeof(*new) * (size += 1))))
		return(NULL);
	new[--size] = 0;
	while (size--)
		new[size] = ' ';
	return (new);
}

/*
** map_measuring keep the lenght of the biggest line and count how
** many lines ther is in the map. It also check if ther is no empty line
** between and if the height of the map is over 2.
*/

int				map_measuring(t_cubfile *cbfile, t_gnl *gnl)
{
	int			len;

	cbfile->d_map[W] = 0;
	cbfile->d_map[H] = 0;
	while ((gnl->ret = get_next_line(gnl->fd, &(gnl->line))))
	{
		if (*(gnl->line) && (++(cbfile->d_map[H]))
				&& (len = ft_strlen(gnl->line)))
			cbfile->d_map[W] = ((len > cbfile->d_map[W]) ?
					len : cbfile->d_map[W]);
		else
		{
			if (cbfile->d_map[H] == 0)
				(gnl->nwline)++;
			else
				return (0);//Empty line in map;
		}
		free(gnl->line);
	}
	if (gnl->ret == -1)
		return (0);//gnl error;
	free(gnl->line);
	return ((cbfile->d_map[H] < 3 ? 0 : 1));
}

/*
** map_cpy check if each character of the current line is
** authorized and copy it in the map line. It also check if there is a
** position character and if it is, if it's the first (it must be only
** one position character (N, S, E, W)). Then record the position. 
** before quiting it checks if the last character is space, 1 or 2.
*/

int				map_cpy(t_cubfile *cbfile, char *line, int h)
{
	int			w;

	w = 0;
	while (*line)
	{
		if (*line == '0' || *line == '1' || *line == ' ' || *line == '2')
			cbfile->map[h][w] = *line;
		else if ((*line == 'N' || *line == 'E' || *line == 'W'
					|| *line == 'S') && cbfile->map_pos[W] == -1)
		{
			cbfile->map[h][w] = *line;
			cbfile->map_pos[W] = w;
			cbfile->map_pos[H] = h;
			cbfile->map_pos[O] = *line;
		}
		else
			return (0);//map error;
		line++;
		w++;
	}
	if (*(line - 1) != '1' && *(line - 1) != ' ' && *(line - 1) != '2')
		return (0);//map error, end of line;
	return (1);
}

/*
** map_recording creates a new adress line of the maximum map size to
** each map board, full it with spaces. Then it get the next line of the map
** and check the first character which must be space 1 or 2.
** Then it copy the line in the map.
*/

int				map_recording(t_cubfile *cbfile, t_gnl *gnl)
{
	int			i;

	i = -1;
	cbfile->map_pos[W] = -1;
	while (++i < cbfile->d_map[H])
	{
		if (!(cbfile->map[i] = ft_strnewpsace(cbfile->d_map[W])))
			return (0);
		if ((get_next_line(gnl->fd, &(gnl->line))) < 0)
			return (0);//gnl error;
		if (*(gnl->line) != ' ' && *(gnl->line) != '1' && *(gnl->line) != '2')
			return (0);//map error, begining of line;
		if (!map_cpy(cbfile, gnl->line, i))
			return (0);
		free(gnl->line);
	}
	cbfile->map[i] = NULL;
	if (cbfile->map_pos[W] == -1)
		return (0);//No player position in map;
	return (1);
}

int				handle_map(t_cubfile *cbfile, t_gnl *gnl, char *file)
{
	int			i;

	if (!map_measuring(cbfile, gnl))
		return (0);
	if (close(gnl->fd) == -1)
		return (0);//close error;
	if (!(cbfile->map = (char**)malloc(sizeof(char*) * (cbfile->d_map[H] + 1))))
		return (0);
	if ((gnl->fd = open(file, O_RDONLY)) < 0)
		return (0);
	i = 0;
	while (i++ < gnl->nwline)
	{
		if (!get_next_line(gnl->fd, &(gnl->line)))
			return (0);//gnl error;
		free(gnl->line);
	}
	if (!map_recording(cbfile, gnl))
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cub_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 18:08:12 by jle-corr          #+#    #+#             */
/*   Updated: 2020/07/23 14:13:21 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				get_color(char *line, t_cubfile *cbfile, int i)
{
	int			c;

	if (!((c = ft_atoi(line)) < 256))
		return (ft_error("color value is too high in .cub"));
	cbfile->colors[--i].rgb.c[2] = c;
	if (!(line = ft_strchr(line, ',')) || !(ft_isdigit(*(line + 1))))
		return (ft_error("Wrong color format in .cub"));
	if (!((c = ft_atoi(++line)) < 256))
		return (ft_error("color value is too high in .cub"));
	cbfile->colors[i].rgb.c[1] = c;
	if (!(line = ft_strchr(line, ',')) || !(ft_isdigit(*(line + 1))))
		return (ft_error("Wrong color format in .cub"));
	if (!((c = ft_atoi(line + 1)) < 256))
		return (ft_error("color value is too high in .cub"));
	cbfile->colors[i].rgb.c[0] = c;
	return (1);
}

int				extract_color_n_res(char *line, t_cubfile *cbfile, int id)
{
	int		i;

	i = 0;
	if (!(ft_isdigit(*line)))
		return (ft_error("wrong color or resolution format in .cub"));
	if ((++i && id == F) || (++i && id == C))
	{
		if (!(get_color(line, cbfile, i)))
			return (0);
	}
	else if (id == R)
	{
		if (((i = ft_atoi(line)) < 10) || (i > 2500))
			return (ft_error("resolution value is wrong in .cub"));
		cbfile->res.w = i;
		while (*line && *line != ' ')
			line++;
		if (((i = ft_atoi(line)) < 10) || (i > 2000))
			return (ft_error("resolution value is wrong in .cub"));
		cbfile->res.h = i;
	}
	else
		return (ft_error("wrong color or resolution format in .cub"));
	return (1);
}

int				extract_elements(char *line, t_cubfile *cbfile)
{
	int			i;
	int			id;

	id = 0;
	i = 0;
	while (*line && *line != ' ')
		id += *line++;
	while (*line && *line == ' ')
		line++;
	if (id == R || id == C || id == F)
	{
		if (!(extract_color_n_res(line, cbfile, id)))
			return (0);
	}
	else if ((++i && id == NO) || (++i && id == SO) || (++i && id == WE)
			|| (++i && id == EA) || (++i && id == S))
	{
		if (!*line || !(cbfile->tx_path[--i] =
					ft_substr(line, 0, ft_strlen(line))))
			return (ft_error("texture path error"));
	}
	else
		return (ft_error(".cub data error"));
	return (++(cbfile->nb_elements));
}

int				handle_elements(t_cubfile *cbfile, t_gnl *gnl)
{
	int			ret;
	int			d;

	gnl->nwline = 0;
	cbfile->nb_elements = 0;
	while (cbfile->nb_elements != 8)
	{
		if ((ret = get_next_line(gnl->fd, &(gnl->line))) < 1)
			return (ret == 0 ? ft_error(".cub not complete") : ft_error("gnl"));
		if (*(gnl->line))
			if (!(extract_elements(gnl->line, cbfile)))
				return (0);
		free(gnl->line);
		(gnl->nwline)++;
	}
	ret = -1;
	while (++ret < 5)
		if ((d = open(cbfile->tx_path[ret], O_RDONLY)) < 0 || close(d) == -1)
			return (ft_error("Couldn't open texture path"));
	return (gnl->nwline);
}

int				extract_cub_file(int ac, char **av, t_cubfile *cbfile)
{
	t_gnl		gnl;

	if (ac < 2 || ac > 3)
		return (ft_error("Wrong nbr of arguments"));
	if ((gnl.fd = open(av[1], O_RDONLY)) < 0 ||
			!(ft_strnstr(av[1], ".cub", ft_strlen(av[1]))))
		return (ft_error("Couldn't open file or wrong format"));
	if (ac == 3)
		if ((cbfile->save = ft_strncmp(av[2], "--save", 6)))
			return (ft_error("Wrong 2nd argument"));
	if (!(handle_elements(cbfile, &gnl)))
		return (0);
	if (!handle_map(cbfile, &gnl, av[1]))
		return (0);
	if (close(gnl.fd) == -1)
		return (0);
	if (!(verify_map(cbfile->map)))
		return (0);
	return (1);
}

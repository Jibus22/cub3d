/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cub_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 18:08:12 by jle-corr          #+#    #+#             */
/*   Updated: 2020/08/08 18:41:27 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				get_color(char *line, t_cubfile *cub, int i)
{
	int			c;
	int			j;

	j = 3;
	while (--j >= 0)
	{
		if (!ft_isdigit(*line))
			return (ft_error("Color value is missing in .cub"));
		if (!((c = ft_atoi(line)) < 256))
			return (ft_error("color value is too high in .cub"));
		cub->colors[i].rgb.c[j] = c;
		if (j > 0)
		{
			if (!(line = ft_strchr(line, ',')))
				return (ft_error("Wrong color format in .cub"));
			line++;
			while (*line && *line == ' ')
				line++;
		}
	}
	return (1);
}

int				extract_color_n_res(char *line, t_cubfile *cub, int id, int i)
{
	i = 0;
	if (!(ft_isdigit(*line)))
		return (ft_error("wrong color or resolution format in .cub"));
	if ((id == F) || (++i && id == C))
	{
		if (!(get_color(line, cub, i)))
			return (0);
	}
	else if (id == R)
	{
		cub->res.w = ft_atoi(line);
		while (*line && *line != ' ')
			line++;
		cub->res.h = ft_atoi(line);
		if (cub->res.w < 10 || cub->res.h < 10)
			return (ft_error("resolution value is too low in .cub"));
		if (cub->res.w > cub->screensize.w && cub->save)
			cub->res.w = cub->screensize.w;
		if (cub->res.h > cub->screensize.h && cub->save)
			cub->res.h = cub->screensize.h;
	}
	else
		return (ft_error("wrong color or resolution format in .cub"));
	return (1);
}

int				extract_elements(char *line, t_cubfile *cub)
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
		if (!(extract_color_n_res(line, cub, id, i)))
			return (0);
	}
	else if ((++i && id == NO) || (++i && id == SO) || (++i && id == WE)
			|| (++i && id == EA) || (++i && id == S))
	{
		if (!*line || !(cub->tx_path[--i] =
					ft_substr(line, 0, ft_strlen(line))))
			return (ft_error("texture path error"));
	}
	else
		return (ft_error(".cub data error"));
	return (++(cub->nb_elements));
}

int				handle_elements(t_cubfile *cub, t_gnl *gnl)
{
	int			ret;
	int			d;

	gnl->nwline = 0;
	cub->nb_elements = 0;
	while (cub->nb_elements != 8)
	{
		if ((ret = get_next_line(gnl->fd, &(gnl->line))) < 1)
			return (ret == 0 ? ft_error(".cub not complete") : ft_error("gnl"));
		if (*(gnl->line))
			if (!(extract_elements(gnl->line, cub)))
				return (0);
		free(gnl->line);
		(gnl->nwline)++;
	}
	ret = -1;
	while (++ret < 5)
		if ((d = open(cub->tx_path[ret], O_RDONLY)) < 0 || close(d) == -1)
			return (ft_error("Couldn't open texture path"));
	return (gnl->nwline);
}

int				extract_cub_file(int ac, char **av, t_cubfile *cub)
{
	t_gnl		gnl;

	if (ac < 2 || ac > 3)
		return (ft_error("Wrong nbr of arguments"));
	if ((gnl.fd = open(av[1], O_RDONLY)) < 0 ||
			!(ft_strnstr(av[1], ".cub", ft_strlen(av[1]))))
		return (ft_error("Couldn't open file or wrong format"));
	cub->save = 1;
	if (ac == 3 && ((cub->save = ft_strncmp(av[2], "--save", 6)) ||
				ft_strlen(av[2]) != 6))
		return (ft_error("Wrong 2nd argument"));
	mlx_get_screen_size(cub->mlx.mlx, &(cub->screensize.w),
			&(cub->screensize.h));
	cub->colors[0].color = 0;
	cub->colors[1].color = 0;
	if (!(handle_elements(cub, &gnl)))
		return (0);
	if (!handle_map(cub, &gnl, av[1]))
		return (0);
	if (close(gnl.fd) == -1)
		return (0);
	if (!(verify_map(cub->map)))
		return (0);
	return (1);
}

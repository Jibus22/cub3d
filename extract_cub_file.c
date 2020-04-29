/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cub_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 18:08:12 by jle-corr          #+#    #+#             */
/*   Updated: 2020/04/29 20:02:30 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				extract_color_n_res(char *line, t_cubfile *cbfile, int id)
{
	int		i;

	i = 0;
	if (!(ft_isdigit(*line)))
		return (0);//Wrong color format in .cub;
	if (id == R && (cbfile->res[0] = ft_atoi(line)) > 0)
	{
		while (*line && *line != ' ')
			line++;
		if ((cbfile->res[1] = ft_atoi(line)) <= 0)
			return (0);//Wrong resolution format in .cub;
	}
	else if ((++i && id == F) || (++i && id == C))
	{
		cbfile->colors[--i][0] = ft_atoi(line);
		if (!(line = ft_strchr(line, ',')) || !(ft_isdigit(*(line + 1))))
				return (0);//Wrong color format in .cub;
		cbfile->colors[i][1] = ft_atoi(++line);
		if (!(line = ft_strchr(line, ',')) || !(ft_isdigit(*(line + 1))))
				return (0);//Wrong color format in .cub;
		cbfile->colors[i][2] = ft_atoi(line + 1);
	}
	else
		return (0);//Wrong resolution or color format;
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
			return (0);//texture path error;
	}
	else
		return (0);//.cub data error
	return(++(cbfile->nb_elements));
}

int				handle_elements(t_cubfile *cbfile, t_gnl *gnl)
{
	int			ret;

	gnl->nwline = 0;
	cbfile->nb_elements = 0;
	while (cbfile->nb_elements != 8)
	{
		if ((ret = get_next_line(gnl->fd, &(gnl->line))) < 1)
			return (ret == 0 ? 0 : -1);//.cub not complete or gnl error;
		if (*(gnl->line))
			if (!(extract_elements(gnl->line, cbfile)))
				return (0);
		free(gnl->line);
		(gnl->nwline)++;
	}
	return (gnl->nwline);
}

int				verify_elements(t_cubfile *cbfile)
{
	int			i;
	int			d;

	i = -1;
	while (++i < 5)
		if ((d = open(cbfile->tx_path[i], O_RDONLY)) < 0 || close(d) == -1)
			return (0);//Couldn't open texture path;
	i = 0;
	d = -1;
	while (++d < 3)
	{
		if (cbfile->colors[i][d] < 0 || cbfile->colors[i][d] > 255)
			return (0);//Wrong color data in .cub file;
		if (d == 2 && i++ == 0)
			d = -1;
	}
	if (cbfile->res[0] < 1 || cbfile->res[0] > 3000 ||
			cbfile->res[1] < 1 || cbfile->res[1] > 3000)
		return (0);//Wrong resolution data in .cub file;
	return (1);
}

int				extract_cub_file(int ac, char **av, t_cubfile *cbfile)
{
	t_gnl		gnl;

	if (ac < 2 || ac > 3)
		return (0);//Wrong nbr of arguments
	if ((gnl.fd = open(av[1], O_RDONLY)) < 0 ||
			!(ft_strnstr(av[1], ".cub", ft_strlen(av[1]))))
		return (0);//Couldn't open file or wrong format
	if (ac == 3)
		if ((cbfile->save = ft_strncmp(av[2], "--save", 6)))
			return (0);//Wrong 2nd argument
	if (!(handle_elements(cbfile, &gnl)))
		return (0);
	if (!verify_elements(cbfile))
		return (0);
	if (!handle_map(cbfile, &gnl, av[1]))
		return (0);
	if (close(gnl.fd) == -1)
		return (0);
	if (!(verify_map(cbfile->map)))
		return (0);
	return (1);
}

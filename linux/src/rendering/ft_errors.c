/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 02:48:28 by jle-corr          #+#    #+#             */
/*   Updated: 2020/08/11 15:27:06 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				ft_error(const char *error)
{
	write(1, "Error:\n", 7);
	write(1, error, ft_strlen(error));
	return (0);
}

int				ft_errorbas(const char *error, t_cubfile *cub)
{
	free(cub->mlx.mlx);
	write(1, "Error:\n", 7);
	write(1, error, ft_strlen(error));
	return (0);
}

int				ft_errorfree(const char *error, char *str,
		t_cubfile *cub, int m)
{
	int			i;

	i = -1;
	while (++i < 5)
		if (cub->tx_path[i])
			free(cub->tx_path[i]);
	if (str)
		free(str);
	free(cub->mlx.mlx);
	if (m > 0)
	{
		write(1, "Error:\n", 7);
		write(1, error, ft_strlen(error));
	}
	return (0);
}

int				ft_freemap(const char *error, int h_map,
		char *str, t_cubfile *cub)
{
	int			i;

	i = -1;
	while (++i <= h_map)
		free(cub->map[i]);
	if (str)
		free(str);
	i = -1;
	while (++i < 5)
		if (cub->tx_path[i])
			free(cub->tx_path[i]);
	free(cub->map);
	free(cub->mlx.mlx);
	write(1, "Error:\n", 7);
	write(1, error, ft_strlen(error));
	return (0);
}

int				ft_freereturn(const char *error, int code, t_cubfile *cub)
{
	int			i;

	i = -1;
	while (++i < 5)
	{
		if (!cub->tex[i].img)
			break;
		else
			mlx_destroy_image(cub->mlx.mlx, cub->tex[i].img);
	}
	ft_freemap(error, cub->d_map.h - 1, NULL, cub);
	if (code == 2)
		free(cub->sprite);
	return (0);
}

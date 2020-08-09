/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 02:48:28 by jle-corr          #+#    #+#             */
/*   Updated: 2020/08/09 03:04:15 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				ft_error(const char *error)
{
	write(1, "Error:\n", 7);
	write(1, error, ft_strlen(error));
	return (0);
}

int				free_txpath(t_cubfile *cub)
{
	int			i;

	i = -1;
	while (++i < 5)
		if (cub->tx_path[i])
			free(cub->tx_path[i]);
	return (0);
}

int				ft_errorfree(const char *error, char *str,
		t_cubfile *cub, int m)
{
	free_txpath(cub);
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
	free_txpath(cub);
	free(cub->map);
	free(cub->mlx.mlx);
	write(1, "Error:\n", 7);
	write(1, error, ft_strlen(error));
	return (0);
}

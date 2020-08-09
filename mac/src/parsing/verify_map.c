/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 16:18:03 by jle-corr          #+#    #+#             */
/*   Updated: 2020/08/09 03:03:26 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				is_wall(char **map, int w, int h, char currentl)
{
	if (w > 0)
	{
		if (map[h][w - 1] == '0' || map[h][w + 1] == '0')
			return (0);
		if (currentl == 'a' || currentl == '-')
			if (map[h - 1][w] == '0' || map[h - 1][w - 1] == '0'
					|| map[h - 1][w + 1] == '0')
				return (0);
		if (currentl == 'a' || currentl == '+')
			if (map[h + 1][w] == '0' || map[h + 1][w - 1] == '0'
					|| map[h + 1][w + 1] == '0')
				return (0);
	}
	else
	{
		if (map[h][w + 1] == '0')
			return (0);
		if (currentl == 'a' || currentl == '-')
			if (map[h - 1][w] == '0' || map[h - 1][w + 1] == '0')
				return (0);
		if (currentl == 'a' || currentl == '+')
			if (map[h + 1][w] == '0' || map[h + 1][w + 1] == '0')
				return (0);
	}
	return ((map[h][w] = '1'));
}

int				verify_map(char **map, t_cubfile *cub)
{
	int			w;
	int			h;
	int			dmaph;

	w = -1;
	h = 0;
	dmaph = cub->d_map.h - 1;
	while (map[h][++w])
		if (map[h][w] != '1' && map[h][w] != '2')
			if (map[h][w] != ' ' ||
					(map[h][w] == ' ' && !is_wall(map, w, h, '+')))
				return (ft_freemap("map wall missing", dmaph, NULL, cub));
	while (((w = -1) > -2) && map[++h + 1])
		while (map[h][++w])
			if (map[h][w] == ' ')
				if (!is_wall(map, w, h, 'a'))
					return (ft_freemap("map wall missing", dmaph, NULL, cub));
	while (map[h][++w])
		if (map[h][w] != '1' && map[h][w] != '2')
			if (map[h][w] != ' ' ||
					(map[h][w] == ' ' && !is_wall(map, w, h, '-')))
				return (ft_freemap("map wall missing", dmaph, NULL, cub));
	return (1);
}

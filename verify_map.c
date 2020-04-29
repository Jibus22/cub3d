/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 16:18:03 by jle-corr          #+#    #+#             */
/*   Updated: 2020/04/29 19:21:37 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				is_wall(char **map, int w, int h, char currentl)
{
	if (w > 0)
	{
		if (map[h][w - 1] == '0' || map[h][w + 1] == '0')
			return (0);//map error, 
		if (currentl == 'a' || currentl == '-')
			if (map[h - 1][w] == '0' || map[h - 1][w - 1] == '0'
					|| map[h - 1][w + 1] == '0')
				return (0);//map error, 
		if (currentl == 'a' || currentl == '+')
			if (map[h + 1][w] == '0' || map[h + 1][w - 1] == '0'
					|| map[h + 1][w + 1] == '0')
				return (0);//map error, 
	}
	else
	{
		if (map[h][w + 1] == '0')
			return (0);//map error, 
		if (currentl == 'a' || currentl == '-')
			if (map[h - 1][w] == '0' || map[h - 1][w + 1] == '0')
				return (0);//map error, 
		if (currentl == 'a' || currentl == '+')
			if (map[h + 1][w] == '0' || map[h + 1][w + 1] == '0')
				return (0);//map error, 
	}
	return (1);
}

int				verify_map(char **map)
{
	int			w;
	int			h;

	w = -1;
	h = 0;
	while (map[h][++w])
		if (map[h][w] != '1' && map[h][w] != '2')
			if (map[h][w] != ' ' ||
					(map[h][w] == ' ' && !is_wall(map, w, h, '+')))
				return (0);
	while (((w = -1) > -2) && map[++h + 1])
		while (map[h][++w])
			if (map[h][w] == ' ')
				if (!is_wall(map, w, h, 'a'))
					return (0);
	while (map[h][++w])
		if (map[h][w] != '1' && map[h][w] != '2')
			if (map[h][w] != ' ' ||
					(map[h][w] == ' ' && !is_wall(map, w, h, '-')))
				return (0);
	return (1);
}

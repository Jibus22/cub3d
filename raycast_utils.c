/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 23:56:28 by jle-corr          #+#    #+#             */
/*   Updated: 2020/07/18 23:51:24 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			initray_y(t_ray *ray, t_cubfile *cub, double angle, double sign)
{
	if ((ray->y.x = cub->pos.x + ((ray->y.y / tan(angle)) * sign)) > 40000.0
			|| ray->y.x < 0.0)
		ray->y.x = 40000.0;
	ray->y.xa = (1.0 / tan(angle)) * sign;
	ray->y.y = cub->pos.y - (ray->y.y * sign);
}

void			initray_x(t_ray *ray, t_cubfile *cub, double angle, double sign)
{
	if ((ray->x.y = cub->pos.y + ((ray->x.x * tan(angle)) * sign)) < 0.0
			|| ray->x.y > 40000.0)
		ray->x.y = 40000.0;
	ray->x.ya = tan(angle) * sign;
	ray->x.x = cub->pos.x - (ray->x.x * sign);
}

void			init_raylen_n_side(t_ray *ray, t_cubfile *cub,
		int tex_one, int tex_two)
{
	int			i;

	i = -1;
	ray->y.len = hypot(ray->y.x - cub->pos.x, cub->pos.y - ray->y.y);
	ray->x.len = hypot(ray->x.x - cub->pos.x, cub->pos.y - ray->x.y);
	ray->shortest_ray = ray->y.len < ray->x.len ? ray->y.len : ray->x.len;
	cub->side = ray->y.len < ray->x.len ? tex_one : tex_two;
	while (++i < cub->sprite_nb)
	{
		if (cub->sprite[i].justhited == 1)
		{
			cub->sprite[i].justhited = -1;
			if (cub->sprite[i].dist < ray->shortest_ray)
			{
				if (cub->sprite[i].firsthit == -1)
					cub->sprite[i].firsthit = cub->col_x;
				cub->sprite[i].lasthit = cub->col_x;
			}
		}
	}
}

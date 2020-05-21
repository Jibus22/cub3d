/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_raycaster.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 17:43:14 by jle-corr          #+#    #+#             */
/*   Updated: 2020/05/21 17:33:14 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** y_axis means y ray (which stops every y grid) & x_axis means x ray
** (which stops every x grid)
*/

double			rayone(double y_axis_y,
		double x_axis_x, double angle, t_cubfile *cub)
{
	t_y_axis	y_axis;
	t_x_axis	x_axis;

	if ((y_axis.x = cub->pos.x + (y_axis_y / tan(angle))) > 40000.0)
		y_axis.x = 4000.0;
	y_axis.xa = 1.0 / tan(angle);
	y_axis_y = cub->pos.y - y_axis_y;
	while (y_axis.x < (double)cub->d_map.w &&
			cub->map[(int)(y_axis_y - 0.1)][(int)y_axis.x] != '1'
			&& (y_axis_y -= 1.0))
		y_axis.x += y_axis.xa;
	y_axis.ray_len = hypot(y_axis.x - cub->pos.x, cub->pos.y - y_axis_y);
	if ((x_axis.y = cub->pos.y - (x_axis_x * tan(angle))) < 0.0)
		x_axis.y = -4000.0;
	x_axis.ya = tan(angle);
	x_axis_x += cub->pos.x;
	while ((int)x_axis.y > 0 &&
			cub->map[(int)x_axis.y][(int)x_axis_x] != '1' && (x_axis_x += 1.0))
		x_axis.y -= x_axis.ya;
	x_axis.ray_len = hypot(x_axis_x - cub->pos.x, cub->pos.y - x_axis.y);
	return (y_axis.ray_len < x_axis.ray_len ? y_axis.ray_len : x_axis.ray_len);
}

double			raytwo(double y_axis_y,
		double x_axis_x, double angle, t_cubfile *cub)
{
	t_y_axis	y_axis;
	t_x_axis	x_axis;

	if ((y_axis.x = cub->pos.x + (y_axis_y / tan(angle))) < 0.0)
		y_axis.x = -4000.0;
	y_axis.xa = 1.0 / tan(angle);
	y_axis_y = cub->pos.y - y_axis_y;
	while (y_axis.x > 0.0 &&
			cub->map[(int)(y_axis_y - 0.1)][(int)y_axis.x] != '1'
			&& (y_axis_y -= 1.0))
		y_axis.x += y_axis.xa;
	y_axis.ray_len = hypot(y_axis.x - cub->pos.x, cub->pos.y - y_axis_y);
	if ((x_axis.y = cub->pos.y + (x_axis_x * tan(angle))) < 0.0)
		x_axis.y = -4000.0;
	x_axis.ya = tan(angle);
	x_axis_x = cub->pos.x - x_axis_x;
	while ((int)x_axis.y > 0.0 &&
			cub->map[(int)x_axis.y][(int)(x_axis_x - 0.1)] != '1'
			&& (x_axis_x -= 1.0))
		x_axis.y += x_axis.ya;
	x_axis.ray_len = hypot(x_axis_x - cub->pos.x, cub->pos.y - x_axis.y);
	return (y_axis.ray_len < x_axis.ray_len ? y_axis.ray_len : x_axis.ray_len);
}

double			raythree(double y_axis_y,
		double x_axis_x, double angle, t_cubfile *cub)
{
	t_y_axis	y_axis;
	t_x_axis	x_axis;

	if ((y_axis.x = cub->pos.x - (y_axis_y / tan(angle))) < 0.0)
		y_axis.x = -4000;
	y_axis.xa = 1.0 / tan(angle);
	y_axis_y += cub->pos.y;
	while ((int)y_axis.x > 0.0 &&
			cub->map[(int)(y_axis_y)][(int)y_axis.x] != '1'
			&& (y_axis_y += 1.0))
		y_axis.x -= y_axis.xa;
	y_axis.ray_len = hypot(y_axis.x - cub->pos.x, cub->pos.y - y_axis_y);
	if ((x_axis.y = cub->pos.y + (x_axis_x * tan(angle))) < 0.0)
		x_axis.y = 4000.0;
	x_axis.ya = tan(angle);
	x_axis_x = cub->pos.x - x_axis_x;
	while (x_axis.y < (double)cub->d_map.h &&
			cub->map[(int)x_axis.y][(int)(x_axis_x - 0.1)] != '1'
			&& (x_axis_x -= 1.0))
		x_axis.y += x_axis.ya;
	x_axis.ray_len = hypot(x_axis_x - cub->pos.x, cub->pos.y - x_axis.y);
	return (y_axis.ray_len < x_axis.ray_len ? y_axis.ray_len : x_axis.ray_len);
}

double			rayfour(double y_axis_y,
		double x_axis_x, double angle, t_cubfile *cub)
{
	t_y_axis	y_axis;
	t_x_axis	x_axis;

	if ((y_axis.x = cub->pos.x + ((y_axis_y / tan(angle)) * -1.0)) > 40000.0)
		y_axis.x = 40000.0;
	y_axis.xa = (1.0 / tan(angle)) * -1.0;
	y_axis_y += cub->pos.y;
	while (y_axis.x < (double)cub->d_map.w &&
			cub->map[(int)(y_axis_y)][(int)y_axis.x] != '1'
			&& (y_axis_y += 1.0))
		y_axis.x += y_axis.xa;
	y_axis.ray_len = hypot(y_axis.x - cub->pos.x, cub->pos.y - y_axis_y);
	if ((x_axis.y = cub->pos.y + ((x_axis_x * tan(angle)) * -1)) > 40000.0
			|| x_axis.y < 0.0)
		x_axis.y = 40000.0;
	x_axis.ya = tan(angle) * -1.0;
	x_axis_x += cub->pos.x;
	while (x_axis.y < (double)cub->d_map.h &&
			cub->map[(int)x_axis.y][(int)x_axis_x] != '1'
			&& (x_axis_x += 1.0))
		x_axis.y += x_axis.ya;
	x_axis.ray_len = hypot(x_axis_x - cub->pos.x, cub->pos.y - x_axis.y);
	return (y_axis.ray_len < x_axis.ray_len ? y_axis.ray_len : x_axis.ray_len);
}

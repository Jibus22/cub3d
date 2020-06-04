/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_raycaster.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 17:43:14 by jle-corr          #+#    #+#             */
/*   Updated: 2020/06/04 13:10:23 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**	rayone, two, three or four each corresponds to a quadrant of the
**	trigonometric circle. One of them is called according to the angle given
**	in parameter.
**	the main process is the same for all.
**
**	There is two rays which are casted : y_grid in a first time, then x_grid.
**
**	We receive the closest y_ray_y or x_ray_x grid in parameter. We first
**	calculate the corresponding y_ray.x or x_ray.y for each of those rays.
**	then we calculate the step xa or ya. their corresponding step in ordinates
**	& abscisses doesn't need calculations cause it is the lenght of a cell = 1.
**
**	then we give back to y_ray_y or x_ray_x their coordinates starting from the
**	player position.
**	Finally, we increment those value y_ray(x & y) & after x_ray(x & y) with
**	their own step values, until we hit a wall cell.
**
**	Before returning the shortest ray, we record the hited side (W,E,N,S) &
**	the x_pos (tex_x) hited, which will be useful to calculate the ratio of
**	the hited cell & by this way give us after the right column texture.
**
**	they only have little differences like the sign of tan()
**	(depending of the angle), the wall side hited or the manner to check the
**	hited cell.
*/

double			rayone(double y_ray_y,
		double x_ray_x, double angle, t_cubfile *cub)
{
	t_y_ray	y_ray;
	t_x_ray	x_ray;

	if ((y_ray.x = cub->pos.x + (y_ray_y / tan(angle))) > 40000.0)
		y_ray.x = 4000.0;
	y_ray.xa = 1.0 / tan(angle);
	y_ray_y = cub->pos.y - y_ray_y;
	while (y_ray.x < (double)cub->d_map.w &&
			cub->map[(int)(y_ray_y - 0.1)][(int)y_ray.x] != '1'
			&& (y_ray_y -= 1.0))
		y_ray.x += y_ray.xa;
	y_ray.len = hypot(y_ray.x - cub->pos.x, cub->pos.y - y_ray_y);
	if ((x_ray.y = cub->pos.y - (x_ray_x * tan(angle))) < 0.0)
		x_ray.y = -4000.0;
	x_ray.ya = tan(angle);
	x_ray_x += cub->pos.x;
	while ((int)x_ray.y > 0 &&
			cub->map[(int)x_ray.y][(int)x_ray_x] != '1' && (x_ray_x += 1.0))
		x_ray.y -= x_ray.ya;
	x_ray.len = hypot(x_ray_x - cub->pos.x, cub->pos.y - x_ray.y);
	cub->tex_x = y_ray.len < x_ray.len ? y_ray.x -
			(int)y_ray.x : x_ray.y - (int)x_ray.y;
	cub->side = y_ray.len < x_ray.len ? TX_NO : TX_EA;
	return (y_ray.len < x_ray.len ? y_ray.len : x_ray.len);
}

double			raytwo(double y_ray_y,
		double x_ray_x, double angle, t_cubfile *cub)
{
	t_y_ray	y_ray;
	t_x_ray	x_ray;

	if ((y_ray.x = cub->pos.x + (y_ray_y / tan(angle))) < 0.0)
		y_ray.x = -4000.0;
	y_ray.xa = 1.0 / tan(angle);
	y_ray_y = cub->pos.y - y_ray_y;
	while (y_ray.x > 0.0 &&
			cub->map[(int)(y_ray_y - 0.1)][(int)y_ray.x] != '1'
			&& (y_ray_y -= 1.0))
		y_ray.x += y_ray.xa;
	y_ray.len = hypot(y_ray.x - cub->pos.x, cub->pos.y - y_ray_y);
	if ((x_ray.y = cub->pos.y + (x_ray_x * tan(angle))) < 0.0)
		x_ray.y = -4000.0;
	x_ray.ya = tan(angle);
	x_ray_x = cub->pos.x - x_ray_x;
	while ((int)x_ray.y > 0.0 &&
			cub->map[(int)x_ray.y][(int)(x_ray_x - 0.1)] != '1'
			&& (x_ray_x -= 1.0))
		x_ray.y += x_ray.ya;
	x_ray.len = hypot(x_ray_x - cub->pos.x, cub->pos.y - x_ray.y);
	cub->tex_x = y_ray.len < x_ray.len ? y_ray.x - (int)y_ray.x :
		ceil(x_ray.y) - x_ray.y;
	cub->side = y_ray.len < x_ray.len ? TX_NO : TX_WE;
	return (y_ray.len < x_ray.len ? y_ray.len : x_ray.len);
}

double			raythree(double y_ray_y,
		double x_ray_x, double angle, t_cubfile *cub)
{
	t_y_ray	y_ray;
	t_x_ray	x_ray;

	if ((y_ray.x = cub->pos.x - (y_ray_y / tan(angle))) < 0.0)
		y_ray.x = -4000;
	y_ray.xa = 1.0 / tan(angle);
	y_ray_y += cub->pos.y;
	while ((int)y_ray.x > 0.0 &&
			cub->map[(int)(y_ray_y)][(int)y_ray.x] != '1'
			&& (y_ray_y += 1.0))
		y_ray.x -= y_ray.xa;
	y_ray.len = hypot(y_ray.x - cub->pos.x, cub->pos.y - y_ray_y);
	if ((x_ray.y = cub->pos.y + (x_ray_x * tan(angle))) < 0.0)
		x_ray.y = 4000.0;
	x_ray.ya = tan(angle);
	x_ray_x = cub->pos.x - x_ray_x;
	while (x_ray.y < (double)cub->d_map.h &&
			cub->map[(int)x_ray.y][(int)(x_ray_x - 0.1)] != '1'
			&& (x_ray_x -= 1.0))
		x_ray.y += x_ray.ya;
	x_ray.len = hypot(x_ray_x - cub->pos.x, cub->pos.y - x_ray.y);
	cub->tex_x = y_ray.len < x_ray.len ? ceil(y_ray.x) - y_ray.x :
		ceil(x_ray.y) - x_ray.y;
	cub->side = y_ray.len < x_ray.len ? TX_SO : TX_WE;
	return (y_ray.len < x_ray.len ? y_ray.len : x_ray.len);
}

double			rayfour(double y_ray_y,
		double x_ray_x, double angle, t_cubfile *cub)
{
	t_y_ray	y_ray;
	t_x_ray	x_ray;

	if ((y_ray.x = cub->pos.x + ((y_ray_y / tan(angle)) * -1.0)) > 40000.0)
		y_ray.x = 40000.0;
	y_ray.xa = (1.0 / tan(angle)) * -1.0;
	y_ray_y += cub->pos.y;
	while (y_ray.x < (double)cub->d_map.w &&
			cub->map[(int)(y_ray_y)][(int)y_ray.x] != '1' && (y_ray_y += 1.0))
		y_ray.x += y_ray.xa;
	y_ray.len = hypot(y_ray.x - cub->pos.x, cub->pos.y - y_ray_y);
	if ((x_ray.y = cub->pos.y + ((x_ray_x * tan(angle)) * -1)) > 40000.0
			|| x_ray.y < 0.0)
		x_ray.y = 40000.0;
	x_ray.ya = tan(angle) * -1.0;
	x_ray_x += cub->pos.x;
	while (x_ray.y < (double)cub->d_map.h &&
			cub->map[(int)x_ray.y][(int)x_ray_x] != '1'
			&& (x_ray_x += 1.0))
		x_ray.y += x_ray.ya;
	x_ray.len = hypot(x_ray_x - cub->pos.x, cub->pos.y - x_ray.y);
	cub->tex_x = y_ray.len < x_ray.len ? ceil(y_ray.x) - y_ray.x :
		x_ray.y - (int)x_ray.y;
	cub->side = y_ray.len < x_ray.len ? TX_SO : TX_EA;
	return (y_ray.len < x_ray.len ? y_ray.len : x_ray.len);
}

double			raycast(t_cubfile *cub, double angle)
{
	if (angle < 90.0)
		return (rayone(cub->pos.y - floor(cub->pos.y),
				ceil(cub->pos.x) - cub->pos.x, angle * TO_RAD, cub));
	else if (angle < 180.0)
		return (raytwo(cub->pos.y - floor(cub->pos.y),
				cub->pos.x - floor(cub->pos.x), angle * TO_RAD, cub));
	else if (angle < 270.0)
		return (raythree(ceil(cub->pos.y) - cub->pos.y,
				cub->pos.x - floor(cub->pos.x), angle * TO_RAD, cub));
	else
		return (rayfour(ceil(cub->pos.y) - cub->pos.y,
				ceil(cub->pos.x) - cub->pos.x, angle * TO_RAD, cub));
}

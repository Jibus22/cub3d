/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_raycaster.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 16:38:38 by jle-corr          #+#    #+#             */
/*   Updated: 2020/06/04 18:09:15 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			record_sprite()
{
	;
}

double			spriterayone(double y_ray_y,
		double x_ray_x, double angle, t_cubfile *cub)
{
	t_y_ray	y_ray;
	t_x_ray	x_ray;

	if ((y_ray.x = cub->pos.x + (y_ray_y / tan(angle))) > 40000.0)
		y_ray.x = 4000.0;
	y_ray.xa = 1.0 / tan(angle);
	y_ray_y = cub->pos.y - y_ray_y;
	while (y_ray.x < (double)cub->d_map.w &&
			cub->map[(int)(y_ray_y - 0.1)][(int)y_ray.x] != '1')
	{
		if (cub->map[(int)(y_ray_y - 0.1)][(int)y_ray.x] == '2')
			record_sprite();
		y_ray_y -= 1.0;
		y_ray.x += y_ray.xa;
	}
	y_ray.len = hypot(y_ray.x - cub->pos.x, cub->pos.y - y_ray_y);
	if ((x_ray.y = cub->pos.y - (x_ray_x * tan(angle))) < 0.0)
		x_ray.y = -4000.0;
	x_ray.ya = tan(angle);
	x_ray_x += cub->pos.x;
	while ((int)x_ray.y > 0 &&
			cub->map[(int)x_ray.y][(int)x_ray_x] != '1')
	{
		if (cub->map[(int)(x_ray.y)][(int)x_ray_x] == '2')
			record_sprite();
		x_ray_x += 1.0;
		x_ray.y -= x_ray.ya;
	}
	x_ray.len = hypot(x_ray_x - cub->pos.x, cub->pos.y - x_ray.y);
	cub->tex_x = y_ray.len < x_ray.len ? y_ray.x -
			(int)y_ray.x : x_ray.y - (int)x_ray.y;
	cub->side = y_ray.len < x_ray.len ? TX_NO : TX_EA;
	return (y_ray.len < x_ray.len ? y_ray.len : x_ray.len);
}

double			spriteraytwo(double y_ray_y,
		double x_ray_x, double angle, t_cubfile *cub)
{
	t_y_ray	y_ray;
	t_x_ray	x_ray;

	if ((y_ray.x = cub->pos.x + (y_ray_y / tan(angle))) < 0.0)
		y_ray.x = -4000.0;
	y_ray.xa = 1.0 / tan(angle);
	y_ray_y = cub->pos.y - y_ray_y;
	while (y_ray.x > 0.0 &&
			cub->map[(int)(y_ray_y - 0.1)][(int)y_ray.x] != '1')
	{
		if (cub->map[(int)(y_ray_y - 0.1)][(int)y_ray.x] == '2')
			record_sprite();
		y_ray_y -= 1.0;
		y_ray.x += y_ray.xa;
	}
	y_ray.len = hypot(y_ray.x - cub->pos.x, cub->pos.y - y_ray_y);
	if ((x_ray.y = cub->pos.y + (x_ray_x * tan(angle))) < 0.0)
		x_ray.y = -4000.0;
	x_ray.ya = tan(angle);
	x_ray_x = cub->pos.x - x_ray_x;
	while ((int)x_ray.y > 0.0 &&
			cub->map[(int)x_ray.y][(int)(x_ray_x - 0.1)] != '1')
	{
		if (cub->map[(int)(x_ray.y)][(int)(x_ray_x - 0.1)] == '2')
			record_sprite();
		x_ray_x -= 1.0;
		x_ray.y += x_ray.ya;
	}
	x_ray.len = hypot(x_ray_x - cub->pos.x, cub->pos.y - x_ray.y);
	cub->tex_x = y_ray.len < x_ray.len ? y_ray.x - (int)y_ray.x :
		ceil(x_ray.y) - x_ray.y;
	cub->side = y_ray.len < x_ray.len ? TX_NO : TX_WE;
	return (y_ray.len < x_ray.len ? y_ray.len : x_ray.len);
}

double			spriteraythree(double y_ray_y,
		double x_ray_x, double angle, t_cubfile *cub)
{
	t_y_ray	y_ray;
	t_x_ray	x_ray;

	if ((y_ray.x = cub->pos.x - (y_ray_y / tan(angle))) < 0.0)
		y_ray.x = -4000;
	y_ray.xa = 1.0 / tan(angle);
	y_ray_y += cub->pos.y;
	while ((int)y_ray.x > 0.0 &&
			cub->map[(int)(y_ray_y)][(int)y_ray.x] != '1')
	{
		if (cub->map[(int)(y_ray_y)][(int)y_ray.x] == '2')
			record_sprite();
		y_ray_y += 1.0;
		y_ray.x -= y_ray.xa;
	}
	y_ray.len = hypot(y_ray.x - cub->pos.x, cub->pos.y - y_ray_y);
	if ((x_ray.y = cub->pos.y + (x_ray_x * tan(angle))) < 0.0)
		x_ray.y = 4000.0;
	x_ray.ya = tan(angle);
	x_ray_x = cub->pos.x - x_ray_x;
	while (x_ray.y < (double)cub->d_map.h &&
			cub->map[(int)x_ray.y][(int)(x_ray_x - 0.1)] != '1')
	{
		if (cub->map[(int)(x_ray.y)][(int)(x_ray_x - 0.1)] == '2')
			record_sprite();
		x_ray_x -= 1.0;
		x_ray.y += x_ray.ya;
	}
	x_ray.len = hypot(x_ray_x - cub->pos.x, cub->pos.y - x_ray.y);
	cub->tex_x = y_ray.len < x_ray.len ? ceil(y_ray.x) - y_ray.x :
		ceil(x_ray.y) - x_ray.y;
	cub->side = y_ray.len < x_ray.len ? TX_SO : TX_WE;
	return (y_ray.len < x_ray.len ? y_ray.len : x_ray.len);
}

double			spriterayfour(double y_ray_y,
		double x_ray_x, double angle, t_cubfile *cub)
{
	t_y_ray	y_ray;
	t_x_ray	x_ray;

	if ((y_ray.x = cub->pos.x + ((y_ray_y / tan(angle)) * -1.0)) > 40000.0)
		y_ray.x = 40000.0;
	y_ray.xa = (1.0 / tan(angle)) * -1.0;
	y_ray_y += cub->pos.y;
	while (y_ray.x < (double)cub->d_map.w &&
			cub->map[(int)(y_ray_y)][(int)y_ray.x] != '1')
	{
		if (cub->map[(int)(y_ray_y)][(int)y_ray.x] == '2')
			record_sprite();
		y_ray_y += 1.0;
		y_ray.x += y_ray.xa;
	}
	y_ray.len = hypot(y_ray.x - cub->pos.x, cub->pos.y - y_ray_y);
	if ((x_ray.y = cub->pos.y + ((x_ray_x * tan(angle)) * -1)) > 40000.0
			|| x_ray.y < 0.0)
		x_ray.y = 40000.0;
	x_ray.ya = tan(angle) * -1.0;
	x_ray_x += cub->pos.x;
	while (x_ray.y < (double)cub->d_map.h &&
			cub->map[(int)x_ray.y][(int)x_ray_x] != '1')
	{
		if (cub->map[(int)(x_ray.y)][(int)x_ray_x] == '2')
			record_sprite();
		x_ray_x += 1.0;
		x_ray.y += x_ray.ya;
	}
	x_ray.len = hypot(x_ray_x - cub->pos.x, cub->pos.y - x_ray.y);
	cub->tex_x = y_ray.len < x_ray.len ? ceil(y_ray.x) - y_ray.x :
		x_ray.y - (int)x_ray.y;
	cub->side = y_ray.len < x_ray.len ? TX_SO : TX_EA;
	return (y_ray.len < x_ray.len ? y_ray.len : x_ray.len);
}

double			spriteraycast(t_cubfile *cub, double angle)
{
	if (angle < 90.0)
		return (spriterayone(cub->pos.y - floor(cub->pos.y),
				ceil(cub->pos.x) - cub->pos.x, angle * TO_RAD, cub));
	else if (angle < 180.0)
		return (spriteraytwo(cub->pos.y - floor(cub->pos.y),
				cub->pos.x - floor(cub->pos.x), angle * TO_RAD, cub));
	else if (angle < 270.0)
		return (spriteraythree(ceil(cub->pos.y) - cub->pos.y,
				cub->pos.x - floor(cub->pos.x), angle * TO_RAD, cub));
	else
		return (spriterayfour(ceil(cub->pos.y) - cub->pos.y,
				ceil(cub->pos.x) - cub->pos.x, angle * TO_RAD, cub));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_ray.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 11:09:13 by jle-corr          #+#    #+#             */
/*   Updated: 2020/05/20 16:52:58 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
double			rayone(double vertic_y, double horizont_x, double angle, t_cubfile *cub)
{
	double		vertic_x;
	double		vertic_xa;
	double		horizont_y;
	double		horizont_ya;
	double		vertic_ray_len;
	double		horizont_ray_len;

	if ((vertic_x = cub->pos.x + (vertic_y / tan(angle))) > 40000.0)
		vertic_x = 40000.0;
	vertic_xa = 1.0 / tan(angle);
	vertic_y = cub->pos.y - vertic_y;
	while (vertic_x < (double)cub->d_map.w &&
			cub->map[(int)(vertic_y - 0.1)][(int)vertic_x] != '1'
			&& (vertic_y -= 1.0))
		vertic_x += vertic_xa;
	vertic_ray_len = hypot(vertic_x - cub->pos.x, cub->pos.y - vertic_y);
	if ((horizont_y = cub->pos.y - (horizont_x * tan(angle))) < 0.0)
		horizont_y = 40000.0;
	horizont_ya = tan(angle);
	horizont_x += cub->pos.x;
	while ((int)horizont_y > 0 &&
			cub->map[(int)horizont_y][(int)horizont_x] != '1'
			&& (horizont_x += 1.0))
		horizont_y -= horizont_ya;
	horizont_ray_len = hypot(horizont_x - cub->pos.x, cub->pos.y - horizont_y);
	return (vertic_ray_len < horizont_ray_len ? vertic_ray_len : horizont_ray_len);
}*/


t_dvec			y_rayone(double y, double angle, t_cubfile *cub)
{
	double		x;
	double		xa;
	t_dvec		yvec;

	yvec.x = 3000;
	yvec.y = 3000;
	if ((x = cub->pos.x + (y / tan(angle))) > 400)
		return (yvec);
	xa = 1 / tan(angle);
	y = cub->pos.y - y;
	while (x < (double)cub->d_map.w && cub->map[(int)(y - 0.1)][(int)x] != '1')
	{
		y -= 1;
		x += xa;
	}
	yvec.x = x;
	yvec.y = y;
	return (yvec);
}

t_dvec			y_raytwo(double y, double angle, t_cubfile *cub)
{
	double		x;
	double		xa;
	t_dvec		yvec;

	yvec.x = 3000;
	yvec.y = 3000;
	if ((x = cub->pos.x + (y / tan(angle))) < 0)
		return (yvec);
	xa = 1 / tan(angle);
	y = cub->pos.y - y;
	while ((int)x > 0 && cub->map[(int)(y - 0.1)][(int)x] != '1')
	{
		y -= 1;
		x += xa;
	}
	yvec.x = x;
	yvec.y = y;
	return (yvec);
}

t_dvec			y_raythree(double y, double angle, t_cubfile *cub)
{
	double		x;
	double		xa;
	t_dvec		yvec;

	yvec.x = 3000.0;
	yvec.y = 3000.0;
	if ((x = cub->pos.x - (y / tan(angle))) < 0.0)
		return (yvec);
	xa = 1.0 / tan(angle);
	y += cub->pos.y;
	while ((int)x > 0 && cub->map[(int)y][(int)x] != '1')
	{
		y += 1.0;
		x -= xa;
	}
	yvec.x = x;
	yvec.y = y;
	return (yvec);
}

t_dvec			y_rayfour(double y, double angle, t_cubfile *cub)
{
	double		x;
	double		xa;
	t_dvec		yvec;

	yvec.x = 3000.0;
	yvec.y = 3000.0;
	if ((x = cub->pos.x + ((y / tan(angle)) * -1.0)) < 0.0)
		return (yvec);
	xa = 1.0 / tan(angle) * -1.0;
	y += cub->pos.y;
	while (x < (double)cub->d_map.w && cub->map[(int)y][(int)x] != '1')
	{
		y += 1.0;
		x += xa;
	}
	yvec.x = x;
	yvec.y = y;
	return (yvec);
}

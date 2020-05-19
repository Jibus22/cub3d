/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_ray.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 11:09:13 by jle-corr          #+#    #+#             */
/*   Updated: 2020/05/17 19:56:51 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

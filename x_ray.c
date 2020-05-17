/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_ray.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 11:08:23 by jle-corr          #+#    #+#             */
/*   Updated: 2020/05/17 03:25:09 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_dvec			x_rayone(double x, double angle, t_cubfile *cub)
{
	double		y;
	double		ya;
	t_dvec		xvec;

	xvec.x = 3000;
	xvec.y = 3000;
	if ((y = cub->pos.y - (x * tan(angle))) < 0)
		return (xvec);
	ya = tan(angle);
	x += cub->pos.x;
	//printf("\n\nXRAY --> x :  %5.2f  || y : %5.2f  || ya : %5.2f ||\n", x, y, ya);
	while ((int)y > 0 && cub->map[(int)y][(int)x] != '1')
	{
		x += 1;
		y -= ya;
	}
	//if ((int)y > 0)
	//	printf("xx : %5.2f || xy : %5.2f || xcell : %c ||\n",
	//			x, y, cub->map[(int)y][(int)x]);
	//ft_pixel_put(&(cub->img[0]), x, y, cub->colors[1].color);
	xvec.x = x;
	xvec.y = y;
	return (xvec);
}

t_dvec			x_raytwo(double x, double angle, t_cubfile *cub)
{
	double		y;
	double		ya;
	t_dvec		xvec;

	xvec.x = 3000;
	xvec.y = 3000;
	if ((y = cub->pos.y + (x * tan(angle))) < 0)
		return (xvec);
	ya = tan(angle);
	x = cub->pos.x - x;
	while ((int)y > 0 && cub->map[(int)y][(int)(x - 0.1)] != '1')
	{
		x -= 1;
		y += ya;
	}
	xvec.x = x;
	xvec.y = y;
	return (xvec);
}

t_dvec			x_raythree(double x, double angle, t_cubfile *cub)
{
	double		y;
	double		ya;
	t_dvec		xvec;

	xvec.x = 3000;
	xvec.y = 3000;
	if ((y = cub->pos.y + (x * tan(angle))) < 0)
		return (xvec);
	ya = tan(angle);
	x = cub->pos.x - x;
	while ((int)y < cub->d_map.h && cub->map[(int)y][(int)(x - 0.1)] != '1')
	{
		x -= 1;
		y += ya;
	}
	xvec.x = x;
	xvec.y = y;
	return (xvec);
}

t_dvec			x_rayfour(double x, double angle, t_cubfile *cub)
{
	double		y;
	double		ya;
	t_dvec		xvec;

	xvec.x = 3000;
	xvec.y = 3000;
	if ((y = cub->pos.y + ((x * tan(angle) * -1))) > 400)
		return (xvec);
	ya = tan(angle) * -1;
	x += cub->pos.x;
	while ((int)y < cub->d_map.h && cub->map[(int)y][(int)x] != '1')
	{
		x += 1;
		y += ya;
	}
	xvec.x = x;
	xvec.y = y;
	return (xvec);
}

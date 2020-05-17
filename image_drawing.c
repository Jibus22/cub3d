/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_drawing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 20:27:03 by jle-corr          #+#    #+#             */
/*   Updated: 2020/05/17 02:59:15 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			printvector(t_dda_ray *dda, t_cubfile *cub)
{
	printf("raystartx.x : %f\nraystartx.y : %f\nangle : %.2f\n", 
	dda->raystartx.x, dda->raystartx.y, cub->pos.a);
}

t_dvec			minvec(t_dvec xvec, t_dvec yvec, t_cubfile *cub)
{
	double		d_x;
	double		d_y;

	d_x = hypot((xvec.x - cub->pos.x), (cub->pos.y - xvec.y));
	d_y = hypot((yvec.x - cub->pos.x), (cub->pos.y - yvec.y));
	return (d_x > d_y ? yvec : xvec);
}

double			dda_raycast(double angle, t_cubfile *cub)
{
	t_dvec		xxx;
	t_dvec		yyy;
	t_dvec		minmin;
	
	printf("\nangle : %5.2f\t", angle);
	if (angle < 90)
	{
		xxx = x_rayone((ceil(cub->pos.x) - cub->pos.x), angle * TO_RAD, cub);
		yyy = y_rayone(cub->pos.y - floor(cub->pos.y), angle * TO_RAD, cub);
		minmin = minvec(xxx, yyy, cub);
		printf("x : %5.2f, y : %5.2f", minmin.x, minmin.y);
		ft_pixel_put(&(cub->img[0]), minmin.x, minmin.y, cub->colors[1].color);
		//return (fmin(x_rayone((ceil(cub->pos.x) - cub->pos.x), angle * TO_RAD, cub),
		//			y_rayone(cub->pos.y - floor(cub->pos.y), angle * TO_RAD, cub)));
	}
	//else if (angle < 180)
		//return (fmin(x_raytwo(cub->pos.x - floor(cub->pos.x), angle * TO_RAD, cub),
		//			y_raytwo(cub->pos.y - floor(cub->pos.y), angle * TO_RAD, cub)));
	/*else if (angle < 270)
		return (fmin(x_raythree(cub->pos.x - floor(cub->pos.x), angle * TO_RAD, cub),
					y_raythree(ceil(cub->pos.y) - cub->pos.y, angle * TO_RAD, cub)));
	else
		return (fmin(x_rayfour((ceil(cub->pos.x) - cub->pos.x), angle * TO_RAD, cub),
					y_rayfour(ceil(cub->pos.y) - cub->pos.y, angle * TO_RAD, cub)));
	*/cub->save = 3;
	return (0);
}

void			image_drawing(t_cubfile *cub)
{
	double		a_start;
	double		raylen;
	int			col;

	cub->pos.a = 40;
	if ((a_start = cub->pos.a + 30) > 360)
		a_start -= 360;
	col = -1;
	raylen = 0;
	printf("start : %-15.8f\n", a_start);
	while (++col < cub->res.w)
	{
		//printf("col %3d, angle %-12.4f", col, a_start);
		raylen = dda_raycast(a_start, cub);
		//draw_column(raylen, col);
		if ((a_start -= cub->cam.angle_gap) < -0.1)
			a_start += 360;
	}
	printf("\nYOYO %-3.3d\n", col);
	return ;
}

/*
*/

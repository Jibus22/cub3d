/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_rendering.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:57:15 by jle-corr          #+#    #+#             */
/*   Updated: 2020/05/17 02:58:53 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			test_print_pos(t_cubfile *cub)
{
	printf("pos.x : %-5.5f |pos.y : %-5.5f |pos.a : %-10.2f |quarter : %.1f\n",\
			cub->pos.x, cub->pos.y, cub->pos.a, cub->quarter);
}

void			render_image(t_cubfile *cub)
{
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->img[0].img, 0, 0);
}

void			ft_pixel_put(t_img *img, int x, int y, unsigned int color)
{
	char		*dst;

	dst = img->adr + ((y * img->size_line) + (x * img->depth / 8));
	*(unsigned int*)dst = color;
}

void			destroy_old_image(t_cubfile *cub)
{
	if (cub->img[cub->alternate].img)
		mlx_destroy_image(cub->mlx.mlx, cub->img[cub->alternate].img);
}

void			*create_new_image(t_cubfile *cub)
{
	int			a;

	if (cub->alternate == 0 && !(a = 0))
		cub->alternate = 1;
	else if (cub->alternate == 1 && (a = 1))
		cub->alternate = 0;
	if (!(cub->img[a].img = mlx_new_image(cub->mlx.mlx, cub->res.w, cub->res.h)))
		return (NULL);
	if (!(cub->img[a].adr = mlx_get_data_addr(cub->img[a].img,
					&(cub->img[a].depth), &(cub->img[a].size_line),
					&(cub->img[a].endian))))
		return (NULL);
	return ((void*)1);
}

int				cub_rendering(t_cubfile *cub)
{
	int			col;
	double		angle;
	t_dvec		xvec;
	t_dvec		yvec;
	double		xlen;
	double		ylen;
	double		h_col;
	double		h_col_hi;
	double		h_col_low;
	int			e;

	col = -1;
	if (cub->newmove == 1)
	{
		printf("\nZBOUB\n");
		if (!create_new_image(cub))
			return (0);
		//image_drawing(cub);
		angle = cub->pos.a + 30;
		printf("pos.x : %4.2f || pos.y %4.2f\n\n", cub->pos.x, cub->pos.y);
		while (++col < cub->res.w)
		{
			e = -1;
			if (angle < 90)
			{
				xvec = x_rayone((ceil(cub->pos.x) - cub->pos.x), angle * TO_RAD, cub);
				yvec = y_rayone(cub->pos.y - floor(cub->pos.y), angle * TO_RAD, cub);
			}
			else if (angle < 180)
			{
				xvec = x_raytwo(cub->pos.x - floor(cub->pos.x), angle * TO_RAD, cub);
				yvec = y_raytwo(cub->pos.y - floor(cub->pos.y), angle * TO_RAD, cub);
			}
			else if (angle < 270)
			{
				xvec = x_raythree(cub->pos.x - floor(cub->pos.x), angle * TO_RAD, cub);
				yvec = y_raythree(ceil(cub->pos.y) - cub->pos.y, angle * TO_RAD, cub);
			}
			else if (angle < 360)
			{
				xvec = x_rayfour((ceil(cub->pos.x) - cub->pos.x), angle * TO_RAD, cub);
				yvec = y_rayfour(ceil(cub->pos.y) - cub->pos.y, angle * TO_RAD, cub);
			}
			angle -= cub->cam.angle_gap;
			xlen = hypot(xvec.x - cub->pos.x, cub->pos.y - xvec.y);
			ylen = hypot(yvec.x - cub->pos.x, cub->pos.y - yvec.y);
			if (xlen < ylen)
			{
				printf("xvex.x : %5.2f || xvec.y : %5.2f ||", xvec.x, xvec.y);
				h_col = cub->res.h / (0.3689 * xlen);
				h_col_hi = (cub->res.h - h_col) / 2;
				h_col_low = (cub->res.h + h_col) / 2;
				while (++e < h_col_hi)
					ft_pixel_put(&(cub->img[0]), col, e, cub->colors[0].color);
				while (e < h_col_low)
				{
					ft_pixel_put(&(cub->img[0]), col, e, 17635);
					e++;
				}
				while (e < cub->res.h)
				{
					ft_pixel_put(&(cub->img[0]), col, e, 18276);
					e++;
				}
				//ft_pixel_put(&(cub->img[0]), xvec.x, xvec.y, cub->colors[1].color);
			}
			else
			{
				//printf("yvex.x : %5.2f || yvec.y : %5.2f ||", yvec.x, yvec.y);
				h_col = cub->res.h / (0.3689 * ylen);
				h_col_hi = (cub->res.h - h_col) / 2;
				h_col_low = (cub->res.h + h_col) / 2;
				while (++e < h_col_hi)
					ft_pixel_put(&(cub->img[0]), col, e, cub->colors[0].color);
				while (e < h_col_low)
				{
					ft_pixel_put(&(cub->img[0]), col, e, 14388893);
					e++;
				}
				while (e < cub->res.h)
				{
					ft_pixel_put(&(cub->img[0]), col, e, 18276);
					e++;
				}
				//ft_pixel_put(&(cub->img[0]), yvec.x, yvec.y, cub->colors[1].color);
			}
			printf(" col : %d || angle : %5.2f ||\n", col, angle);
			//printf("xlen : %5.2f || ylen : %5.2f || col : %d || angle : %5.2f ||\n",
			//		xlen, ylen, col, angle);
		}
		render_image(cub);
		destroy_old_image(cub);
		//test_print_pos(cub);
		cub->newmove = 0;
		printf("\nZBEB\n");
	}
	else
		return (0);
	return (1);
}

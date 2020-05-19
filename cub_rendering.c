/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_rendering.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:57:15 by jle-corr          #+#    #+#             */
/*   Updated: 2020/05/19 14:59:31 by jle-corr         ###   ########.fr       */
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
	double		anglecam;
	t_dvec		xvec;
	t_dvec		yvec;
	double		xlen;
	double		ylen;
	double		h_col;
	double		h_col_hi;
	double		h_col_low;
	int			e;

	h_col_hi = 0;
	h_col_low = 0;
	h_col = 0;
	col = -1;
	if (cub->newmove == 1)//On ne calcul et dessine que si une touche a ete appuyée (== != pos)
	{
		printf("\nZBOUB\n");
		if (!create_new_image(cub))
			return (0);
		//image_drawing(cub);
		angle = cub->pos.a + (PLAYER_FOV / 2);
		anglecam = angle - angle + (PLAYER_FOV / 2);
		printf("pos.x : %4.2f || pos.y %4.2f || anglestart %4.2f\n\n",
				cub->pos.x, cub->pos.y, angle);
		while (++col < cub->res.w)//A chaque colonne (pixel W) un lancer de rayon
		{
			if (angle < 0.0)
				angle += 360.0;
			else if (angle >= 360.0)
				angle -= 360.0;
			e = -1;
			if (angle < 90.0)//selon l'angle du joueur les calculs sont differents
			{
				xvec = x_rayone((ceil(cub->pos.x) - cub->pos.x), angle * TO_RAD, cub);
				yvec = y_rayone(cub->pos.y - floor(cub->pos.y), angle * TO_RAD, cub);
			}
			else if (angle < 180.0)
			{
				xvec = x_raytwo(cub->pos.x - floor(cub->pos.x), angle * TO_RAD, cub);
				yvec = y_raytwo(cub->pos.y - floor(cub->pos.y), angle * TO_RAD, cub);
			}
			else if (angle < 270.0)
			{
				yvec = y_raythree(ceil(cub->pos.y) - cub->pos.y, angle * TO_RAD, cub);
				xvec = x_raythree(cub->pos.x - floor(cub->pos.x), angle * TO_RAD, cub);
			}
			else if (angle < 360.0)
			{
				yvec = y_rayfour(ceil(cub->pos.y) - cub->pos.y, angle * TO_RAD, cub);
				xvec = x_rayfour((ceil(cub->pos.x) - cub->pos.x), angle * TO_RAD, cub);
			}
			xlen = hypot(xvec.x - cub->pos.x, cub->pos.y - xvec.y);//On finit par avoir les len
			ylen = hypot(yvec.x - cub->pos.x, cub->pos.y - yvec.y);//horizontale et verticales
			if (xlen < ylen)//On choisit la plus courte
			{
				xlen *= cos(anglecam * TO_RAD);//Correction optique de la longueur
				if ((h_col = ((double)cub->cam.d_cam / (1.0 * xlen))) > (double)cub->res.h)
					h_col = (double)cub->res.h;//Caclcul de la taille de la colonne a dessiner
				h_col_hi = ((double)cub->res.h - h_col) / 2.0;//calcul colonne haute (ceil)
				h_col_low = ((double)cub->res.h + h_col) / 2.0;//calcul colonne basse (floor)
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
			}
			else
			{
				ylen *= cos(anglecam * TO_RAD);
				if ((h_col = ((double)cub->cam.d_cam / (1.0 * ylen))) > (double)cub->res.h)
					h_col = (double)cub->res.h;//Si h_col > res.h, les calculs hi&low sont faux(<0)
				h_col_hi = ((double)cub->res.h - h_col) / 2.0;
				h_col_low = ((double)cub->res.h + h_col) / 2.0;
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
			}
			angle -= cub->cam.angle_gap;//On passe au rayon suivant, colonne suivante, pixl suivant
			anglecam -= cub->cam.angle_gap;//angle suivant
		}
		render_image(cub);//put image to window
		destroy_old_image(cub);
		//test_print_pos(cub);
		cub->newmove = 0;// Cest fait, on reset newmove a 0, il sera remis a 1 si commande
		printf("\nZBEB\n");
	}
	else
		return (0);
	return (1);
}

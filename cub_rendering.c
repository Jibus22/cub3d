/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_rendering.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:57:15 by jle-corr          #+#    #+#             */
/*   Updated: 2020/05/20 16:55:17 by jle-corr         ###   ########.fr       */
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
	if (cub->newmove == 1)//On ne calcul et dessine que si une touche a ete appuyée (== != pos)
	{
		printf("\nZBOUB\n");
		if (!create_new_image(cub))
			return (0);
		image_drawing(cub);
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

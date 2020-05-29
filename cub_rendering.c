/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_rendering.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:57:15 by jle-corr          #+#    #+#             */
/*   Updated: 2020/05/29 11:50:54 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			test_print_pos(t_cubfile *cub)
{
	printf("pos.x : %-5.5f |pos.y : %-5.5f |pos.a : %-10.2f |quarter : %.1f\n",\
			cub->pos.x, cub->pos.y, cub->pos.a, cub->quarter);
}

void			ft_pixel_put(t_img *img, int x, int y, unsigned int color)
{
	char		*dst;

	dst = img->adr + ((y * img->size_line) + (x * img->depth / 8));
	*(unsigned int*)dst = color;
}

int				cub_rendering(t_cubfile *cub)
{
		printf("||ZBOUB  ");
	if (cub->newmove == 1)
		image_drawing(cub);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->img[0].img, 0, 0);
	//test_print_pos(cub);
	cub->newmove = 0;// Cest fait, on reset newmove a 0, il sera remis a 1 si commande
	printf("ZBEB||\t");
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 18:44:30 by jle-corr          #+#    #+#             */
/*   Updated: 2020/05/10 18:53:03 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			printcubdata(t_cubfile *cbfile)
{
	printf("NO :%s\n", cbfile->tx_path[0]);
	printf("SO :%s\n", cbfile->tx_path[1]);
	printf("WE :%s\n", cbfile->tx_path[2]);
	printf("EA :%s\n", cbfile->tx_path[3]);
	printf("S :%s\n", cbfile->tx_path[4]);
	printf("res W & H :%d %d\n", cbfile->res.w, cbfile->res.h);
	printf("Floor color :%d,%d,%d,%u\n", cbfile->colors[0].rgb.c[0], cbfile->colors[0].rgb.c[1],\
			cbfile->colors[0].rgb.c[2], cbfile->colors[0].color);
	printf("Ceili color :%d,%d,%d,%u\n", cbfile->colors[1].rgb.c[0],cbfile->colors[1].rgb.c[1],\
			cbfile->colors[1].rgb.c[2], cbfile->colors[1].color);
	printf("\ndimension map w - h : %d - %d\n", cbfile->d_map.w, cbfile->d_map.h);
	printf("coordonnées joueur map w - h - o : %f - %f - %f\n\n",\
			cbfile->pos.x, cbfile->pos.y, cbfile->pos.a);
	while (*cbfile->map)
		printf("%s\n", *cbfile->map++);
}

void			*cubd(t_cubfile *cub, char *av)
{
	int			c;
	int			r;
	int			e;

	c = 0;
	r = 250;
	e = 250;
	if (!(cub->mlx.mlx = mlx_init()))
		return (NULL);
	if (!(cub->mlx.win = mlx_new_window(cub->mlx.mlx, cub->res.w, cub->res.h, av)))
		return (NULL);
	cub->newmove = 1;
	cub->alternate = 0;
	cub->img[1].img = NULL;
	mlx_key_hook(cub->mlx.win, key_event, cub);
	/*while (e-- > 200)
	{
		while (r-- > 200)
			mlx_pixel_put(mlx.mlx_p, mlx.win_p, e, r, cub->colors[0].color);
		r = 250;
	}*/
	/*if (!(mlx.img_p = mlx_xpm_file_to_image(mlx.mlx_p, cub->tx_path[4],
	//				&(cub->res[0]), &(cub->res[1]))))
	//	return (NULL);
	mlx_put_image_to_window(mlx.mlx_p, mlx.win_p, mlx.img_p, 0, 0);*/
	mlx_loop_hook(cub->mlx.mlx, cub_rendering, cub);
	mlx_loop(cub->mlx.mlx);
	return ((void*)1);
}

int				main(int ac, char **av)
{
	t_cubfile	cbfile;

	if (!(extract_cub_file(ac, av, &cbfile)))
		return (-1);
	//printcubdata(&cbfile);
	if (!cubd(&cbfile, av[1]))
		return (0);
	//printf("%.58f\n%.58f\n%.58f\n%.58f\n%.58f\n", ((M_PI + M_PI_2) + (M_PI / 12) + (M_PI / 12) + (M_PI / 12) + (M_PI / 12) + (M_PI / 12)), (2 * M_PI - (M_PI / 12)),
	//		(M_PI + (M_PI / 2)), (1.5 * M_PI + (2 * (M_PI / 12))), (20 * (M_PI / 12)));
	//system("leaks a.out");
	return (0);
}

/*
 *
*/

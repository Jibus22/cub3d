/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 18:44:30 by jle-corr          #+#    #+#             */
/*   Updated: 2020/05/08 16:54:18 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
int		cubd()
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1100, 1100, "essai mlx");
	mlx_loop(mlx_ptr);
}*/

void			printcubdata(t_cubfile *cbfile)
{
	printf("NO :%s\n", cbfile->tx_path[0]);
	printf("SO :%s\n", cbfile->tx_path[1]);
	printf("WE :%s\n", cbfile->tx_path[2]);
	printf("EA :%s\n", cbfile->tx_path[3]);
	printf("S :%s\n", cbfile->tx_path[4]);
	printf("res W & H :%d %d\n", cbfile->res.w, cbfile->res.h);
	printf("Floor color :%d,%d,%d\n", cbfile->colors[0].rgb.c[0],cbfile->colors[0].rgb.c[1],\
			cbfile->colors[0].rgb.c[2]);
	printf("Ceili color :%d,%d,%d\n", cbfile->colors[1].rgb.c[0],cbfile->colors[1].rgb.c[1],\
			cbfile->colors[1].rgb.c[2]);
	printf("\ndimension map w - h : %d - %d\n", cbfile->d_map.w, cbfile->d_map.h);
	printf("coordonnées joueur map w - h - o : %f - %f - %f\n\n",\
			cbfile->pos.x, cbfile->pos.y, cbfile->pos.a);
	while (*cbfile->map)
		printf("%s\n", *cbfile->map++);
}

int				rendertest(t_cubfile *cub)
{
	if (cub->newmove == 1)
	{
		printf("pos.x : %-10f |pos.y : %-10f |pos.a : %-10f\n",\
				cub->pos.x, cub->pos.y, cub->pos.a);
		cub->newmove = 0;
	}
	else
		return (0);
	return (1);
}

void			*cubd(t_cubfile *cub, char *av)
{
	t_graphic	mlx;
	int			c;
	int			r;
	int			e;

	c = 0;
	r = 250;
	e = 250;
	cub->fd = open("action.log", O_RDWR | O_CREAT | O_APPEND);
	if (!(mlx.mlx_p = mlx_init()))
		return (NULL);
	if (!(mlx.win_p = mlx_new_window(mlx.mlx_p, cub->res.w, cub->res.h, av)))
		return (NULL);
	mlx_key_hook(mlx.win_p, key_event, cub);
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
	mlx_loop_hook(mlx.mlx_p, rendertest, cub);
	mlx_loop(mlx.mlx_p);
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
//	system("leaks a.out");
	return (0);
}

/*
 *
*/

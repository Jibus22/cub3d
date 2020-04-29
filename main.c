/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 18:44:30 by jle-corr          #+#    #+#             */
/*   Updated: 2020/04/29 20:03:12 by jle-corr         ###   ########.fr       */
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

int				main(int ac, char **av)
{
	t_cubfile	cbfile;

	if (!(extract_cub_file(ac, av, &cbfile)))
		return (-1);
	printf("NO :%s\n", cbfile.tx_path[0]);
	printf("SO :%s\n", cbfile.tx_path[1]);
	printf("WE :%s\n", cbfile.tx_path[2]);
	printf("EA :%s\n", cbfile.tx_path[3]);
	printf("S :%s\n", cbfile.tx_path[4]);
	printf("res W & H :%d %d\n", cbfile.res[0], cbfile.res[1]);
	printf("Floor color :%d,%d,%d\n", cbfile.colors[0][0],cbfile.colors[0][1],\
			cbfile.colors[0][2]);
	printf("Ceili color :%d,%d,%d\n", cbfile.colors[1][0],cbfile.colors[1][1],\
			cbfile.colors[1][2]);
	printf("\ndimension map w - h : %d - %d\n", cbfile.d_map[W], cbfile.d_map[H]);
	printf("coordonnées joueur map w - h - o : %d - %d - %d\n\n",\
			cbfile.map_pos[W], cbfile.map_pos[H], cbfile.map_pos[O]);
	while (*cbfile.map)
		printf("%s\n", *cbfile.map++);
//	system("leaks a.out");
	return (0);
}

/*
 *
*/

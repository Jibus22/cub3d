/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 18:44:30 by jle-corr          #+#    #+#             */
/*   Updated: 2020/07/21 18:04:59 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			printcubdata(t_cubfile *cbfile)
{
	int			i;

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
	i = -1;
	while (++i < cbfile->d_map.h)
		printf("%s\n", cbfile->map[i]);
}

void			*create_new_image(t_cubfile *cub)
{
	if (!(cub->img[0].img = mlx_new_image(cub->mlx.mlx, cub->res.w, cub->res.h)))
		return (NULL);
	if (!(cub->img[0].adr = mlx_get_data_addr(cub->img[0].img,
					&(cub->img[0].depth), &(cub->img[0].size_line),
					&(cub->img[0].endian))))
		return (NULL);
	return ((void*)1);
}

int				init_textures(t_cubfile *cub)
{
	int			i;
	//Choper et stocker la data de chaque fichier .xpm
	i = -1;
	while (++i < 5)
	{
		if (!(cub->tex[i].img = mlx_xpm_file_to_image(cub->mlx.mlx,
						cub->tx_path[i], &(cub->tex[i].w),
						&(cub->tex[i].h))))	
			return (ft_error("Couldn't load a texture xpm file"));
		cub->tex[i].adr = mlx_get_data_addr(cub->tex[i].img,
				&(cub->tex[i].depth), &(cub->tex[i].size_line),
				&(cub->tex[i].endian));
	}
	return (1);
}

/*int				quit_cub(t_cubfile *cub)
{
	if (cub->run == 0)
		exit(0);
	return (0);
}*/

int				init_sprite(t_cubfile *cub)
{
	if (!(cub->sprite = malloc(sizeof(t_sprite) * cub->sprite_nb)))
		return (0);
	return (1);
}

void			*cubd(t_cubfile *cub, char *av)
{
	if (!(cub->mlx.mlx = mlx_init()))
		return (NULL);
	if (!(cub->mlx.win = mlx_new_window(cub->mlx.mlx, cub->res.w, cub->res.h, av)))
		return (NULL);
	cub->run = 1;
	cub->newmove = 1;//permet de lancer la premiere image sans pour autant appuyer sur une touche
	cub->img[1].img = NULL;
	cub->cam.d_cam = fabs(cub->res.w / DCAM_DIVIDER);//distance player-ecran pour garder 60fov
	cub->cam.angle_gap = PLAYER_FOV / (double)(cub->res.w);//angle entre chaque pixel /raycasts
	if (!(init_textures(cub)))
		return (NULL);
	if (!(init_sprite(cub)))
		return (NULL);
	if (!(create_new_image(cub)))
		return (NULL);
	//system("leaks a.out");
	mlx_hook(cub->mlx.win, KEYPRESS, 1L << 0, key_event, cub);//met newmove a 1 et modifie t_pos
	//mlx_hook(cub->mlx.win, 17L, 0, quit_cub, cub);
	mlx_loop_hook(cub->mlx.mlx, image_drawing, cub);//Si newmove==1,crea nvx calcul
	mlx_loop(cub->mlx.mlx);
	return ((void*)1);
}

int				main(int ac, char **av)
{
	t_cubfile	cbfile;

	if (!(extract_cub_file(ac, av, &cbfile)))
		return (-1);
	printcubdata(&cbfile);
	if (!cubd(&cbfile, av[1]))
		return (0);
	//system("leaks a.out");
	return (0);
}

/*
 *
*/

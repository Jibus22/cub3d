/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 18:44:30 by jle-corr          #+#    #+#             */
/*   Updated: 2020/08/06 23:16:21 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "bmp.h"

void			*create_new_image(t_cubfile *cub, int nb)
{
	int			i;

	i = -1;
	while (++i < nb)
	{
		if (!(cub->img[i].img = mlx_new_image(cub->mlx.mlx,
						cub->res.w, cub->res.h)))
			return (NULL);
		if (!(cub->img[i].adr = mlx_get_data_addr(cub->img[i].img,
						&(cub->img[i].depth), &(cub->img[i].size_line),
						&(cub->img[i].endian))))
			return (NULL);
	}
	return ((void*)1);
}

int				init_cub(t_cubfile *cub)
{
	int			i;

	cub->newmove = 1;
	cub->cam.d_cam = fabs(cub->res.w / (2 * tan((PLAYER_FOV / 2) * TO_RAD)));
	cub->cam.angle_gap = PLAYER_FOV / (double)(cub->res.w);
	cub->imgbuf = 0;
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
	if (!(cub->sprite = (t_sprite*)malloc(sizeof(*(cub->sprite)) *
					cub->sprite_nb)))
		return (ft_error("Couldn't malloc sprites"));
	if (!(create_new_image(cub, 1)))
		return (ft_error("Couldn't create mlx image"));
	return (1);
}

int				quit_cub(t_cubfile *cub)
{
	int			i;

	i = -1;
	while (++i < 5)
		mlx_destroy_image(cub->mlx.mlx, cub->tex[i].img);
	mlx_destroy_image(cub->mlx.mlx, cub->img[0].img);
	free(cub->sprite);
	if (cub->save)
		mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
	exit(0);
	return (0);
}

int				main(int ac, char **av)
{
	t_cubfile	cub;

	if (!(extract_cub_file(ac, av, &cub)))
		return (-1);
	if (!(cub.mlx.mlx = mlx_init()))
		return (-1);
	if (!(init_cub(&cub)))
		return (-1);
	if (cub.save == 0)
	{
		restore_sprite(&cub);
		wall_drawing(&cub);
		sprite_drawing(&cub);
		save_bmp(&cub, av[1]);
		quit_cub(&cub);
	}
	if (!(cub.mlx.win = mlx_new_window(cub.mlx.mlx,
					cub.res.w, cub.res.h, av[1])))
		return (ft_error("Failed to create mlx window"));
	mlx_hook(cub.mlx.win, KEYPRESS, 1L << 0, key_event, &cub);
	mlx_hook(cub.mlx.win, DESTROYNOTIFY, 0, quit_cub, &cub);
	mlx_loop_hook(cub.mlx.mlx, image_drawing, &cub);
	mlx_loop(cub.mlx.mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 18:44:30 by jle-corr          #+#    #+#             */
/*   Updated: 2020/08/10 14:58:35 by jle-corr         ###   ########.fr       */
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

int				init_cub(t_cubfile *c)
{
	int			i;

	c->newmove = 1;
	c->cam.d_cam = fabs(c->res.w / (2 * tan((PLAYER_FOV / 2) * TO_RAD)));
	c->cam.angle_gap = PLAYER_FOV / (double)(c->res.w);
	i = -1;
	while (++i < 5)
	{
		c->tex[i].img = NULL;
		if (!(c->tex[i].img = mlx_xpm_file_to_image(c->mlx.mlx,
						c->tx_path[i], &(c->tex[i].w),
						&(c->tex[i].h))))
			return (ft_freereturn("Couldn't load xpm", 0, c));
		c->tex[i].adr = mlx_get_data_addr(c->tex[i].img,
				&(c->tex[i].depth), &(c->tex[i].size_line),
				&(c->tex[i].endian));
	}
	if (!(c->sprite = (t_sprite*)malloc(sizeof(*(c->sprite)) *
					c->sprite_nb)))
		return (ft_freereturn("Couldn't malloc sprites", 0, c));
	if (!(create_new_image(c, 1)))
		return (ft_freereturn("Couldn't create mlx image", 2, c));
	return (1);
}

int				quit_cub(t_cubfile *cub)
{
	int			i;

	i = -1;
	while (++i < 5)
		mlx_destroy_image(cub->mlx.mlx, cub->tex[i].img);
	mlx_destroy_image(cub->mlx.mlx, cub->img[0].img);
	i = -1;
	while (++i < 5)
		free(cub->tx_path[i]);
	i = -1;
	while (++i < cub->d_map.h)
		free(cub->map[i]);
	free(cub->map);
	free(cub->sprite);
	if (cub->save)
		mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
	free(cub->mlx.mlx);
	exit(0);
	return (0);
}

int				refresh(t_cubfile *cub)
{
	cub->newmove = 1;
	return (1);
}

int				main(int ac, char **av)
{
	t_cubfile	cub;

	if (!(cub.mlx.mlx = mlx_init()))
		return (-1);
	if (!(extract_cub_file(ac, av, &cub)))
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
		return (ft_freemap("mlx win failed", cub.d_map.h - 1, NULL, &cub));
	mlx_hook(cub.mlx.win, KEYPRESS, 1L << 0, key_event, &cub);
	mlx_hook(cub.mlx.win, DESTROYNOTIFY, 0, quit_cub, &cub);
	mlx_hook(cub.mlx.win, 15, 1L << 16, refresh, &cub);
	mlx_loop_hook(cub.mlx.mlx, image_drawing, &cub);
	mlx_loop(cub.mlx.mlx);
	return (0);
}

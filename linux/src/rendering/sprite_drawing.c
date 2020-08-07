/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_drawing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 12:41:21 by jle-corr          #+#    #+#             */
/*   Updated: 2020/08/06 00:58:36 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			sortsprites(t_cubfile *cub)
{
	int			i;
	t_sprite	tmp;

	i = 1;
	while (i < cub->sprite_nb)
	{
		if (cub->sprite[i - 1].dist < cub->sprite[i].dist)
		{
			tmp = cub->sprite[i - 1];
			cub->sprite[i - 1] = cub->sprite[i];
			cub->sprite[i] = tmp;
			i = 1;
		}
		else
			i++;
	}
}

void			initialize_sprite_display(t_cubfile *cub,
		t_spritedisplay *screen, t_sprite *sprite)
{
	screen->ratio_x = (double)cub->tex[TX_SPRITE].w / (double)sprite->width;
	screen->ratio_y = (double)cub->tex[TX_SPRITE].h /
		(double)sprite->height;
	screen->y_start = cub->res.h > sprite->height ?
		(cub->res.h - sprite->height) / 2 : 0;
	screen->y_end = sprite->height > cub->res.h ? cub->res.h :
		(cub->res.h + sprite->height) / 2;
	screen->tex_wall_y = sprite->height < cub->res.h ? 0 :
		(sprite->height - cub->res.h) / 2;
	if (sprite->firsthit > sprite->left)
	{
		screen->x_start = sprite->firsthit;
		screen->tex_wall_x = (sprite->firsthit - sprite->left);
	}
	else
	{
		screen->x_start = sprite->left;
		screen->tex_wall_x = 0;
	}
	if (sprite->lasthit > sprite->right)
		screen->x_end = sprite->right;
	else
		screen->x_end = sprite->lasthit + 1;
}

/*
** sprite_drawing first sort initialized sprites by distance. The more far
** is the first to draw, and then.
** Then it draws to the screen by few calculations the final sprite.
*/

void			draw_line(t_cubfile *cub, t_spritedisplay sc, int tex_y)
{
	int			tex_x;
	t_color		color;

	while (sc.x_start < sc.x_end)
	{
		tex_x = (int)(sc.ratio_x * (sc.tex_wall_x)++);
		color = ft_get_color(&(cub->tex[TX_SPRITE]), tex_x, tex_y);
		if (color.color)
			ft_pixel_put(&(cub->img[0]), sc.x_start, sc.y_start, color.color);
		(sc.x_start)++;
	}
}

void			sprite_drawing(t_cubfile *cub)
{
	int				i;
	int				tex_y;
	t_spritedisplay	screen;

	sortsprites(cub);
	i = -1;
	while (++i < cub->sprite_nb && cub->sprite[i].dist > 0.0)
	{
		initialize_sprite_display(cub, &screen, &(cub->sprite[i]));
		while (screen.y_start < screen.y_end)
		{
			tex_y = (int)(screen.ratio_y * (screen.tex_wall_y)++);
			draw_line(cub, screen, tex_y);
			(screen.y_start)++;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 17:00:50 by jle-corr          #+#    #+#             */
/*   Updated: 2020/08/06 01:23:14 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** initialize_sprite calculate all the theorical sprite display on the
** projection screen, using vector tools. It will be later compared to the
** real hits, to display the correct part of sprite.
** when a '2' cell is hited, it means the sprite is at the center of this cell,
** then the distance player-spritecenter is calculated. It permits us to
** calculate the width and height of the sprite.
** Then, to find the theorical beginning and end of sprite display, we have to
** find the angle between the left of FOV (player angle direction + FOV / 2)
** and the player-sprite vector. Therefore we can with the help of this angle
** calculate the corresponding pixel of the screen projection with the sprite.
** So we have the center of it, and to find the left and right (start and end)
** of the sprite, we just have to substract or add it by half of width.
*/

void			sprite_angle_calculation(t_sprite *sp, t_cubfile *cub)
{
	sp->alpha = cub->pos.a + (PLAYER_FOV / 2);
	if (sp->alpha >= 360.0)
		sp->alpha -= 360.0;
	if (sp->vy < 0.0)
		sp->alpha -= (acos(sp->vx / sp->dist) / TO_RAD);
	else
		sp->alpha -= (360.0 - (acos(sp->vx / sp->dist) / TO_RAD));
	if (sp->alpha < 0.0)
		sp->alpha += 360.0;
	if (sp->alpha > 270.0)
		sp->alpha -= 360.0;
}

void			initialize_sprite(t_sprite *sp, int y, int x, t_cubfile *cub)
{
	sp->cell.w = x;
	sp->cell.h = y;
	sp->vx = x + 0.5 - cub->pos.x;
	sp->vy = y + 0.5 - cub->pos.y;
	sp->dist = hypot(sp->vx, sp->vy);
	sprite_angle_calculation(sp, cub);
	if (sp->alpha > -10.0 && sp->alpha < 70.0)
		sp->dist *= cos((sp->alpha - 30.0) * TO_RAD);
	else
		sp->dist *= sp->alpha < -10.0 ? cos(TO_RAD * -40.0) :
			cos(TO_RAD * 40.0);
	sp->width = cub->cam.d_cam / sp->dist;
	sp->height = sp->width;
	sp->mid = sp->alpha / cub->cam.angle_gap;
	sp->left = sp->mid - (sp->width / 2);
	sp->right = sp->mid + (sp->width / 2);
	sp->justhited = 1;
}

/*
** record_sprite is called when a '2' is hited while raycasting. It check all
** the malloced sprites to watch if the '2' cell currently hited match with
** one of them. If yes, it means it was a sprite already initialized (their
** cell coordinates were already given and permited to match), then we just
** have to fullfill the 'lasthit' variable, corresponding to the pixel of
** the projection screen of the current ray casted.
** else, it means that the curent cell don't have any sprite corresponding.
** therefore we have to initialize an empty sprite corresponding to this one.
*/

int				record_sprite(t_cubfile *cub, int ycell, int xcell)
{
	int			i;

	i = -1;
	while (++i < cub->sprite_nb)
	{
		if (cub->sprite[i].cell.w == xcell && cub->sprite[i].cell.h == ycell)
		{
			cub->sprite[i].justhited = 1;
			return ((cub->i_sprite = i));
		}
	}
	if (i == cub->sprite_nb)
	{
		i = -1;
		while (++i < cub->sprite_nb)
		{
			if (cub->sprite[i].dist < 0.0)
			{
				initialize_sprite(&(cub->sprite[i]), ycell, xcell, cub);
				return ((cub->i_sprite = i));
			}
		}
	}
	return ((cub->i_sprite = -1));
}

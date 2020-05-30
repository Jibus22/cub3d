/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_drawing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 20:27:03 by jle-corr          #+#    #+#             */
/*   Updated: 2020/05/30 18:39:35 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**	column_drawing calculates with the help of the raylen casted & the cam.dcam
**	the lenght of the wall.

**	cam.dcam is the distance between the camera and the
**	screen, which is calculated at the beginning in order to keep the FOV
**	coherent. camera, FOV & screen forms a triangle. If screen get bigger & we
**	must keep the same FOV angle, the distance between camera & screen  must
**	get bigger also.
**
**	To get lenght of the wall, this is an inverse ratio with the lenght of the
**	casted ray. More the ray is long, less the wall is high. So we divide the
**	d_cam value by the lenght of ray.
**
**	To deduces the floor & ceil, we know they both have the same value which is
**	the height screen resolution less the lenght of the wall column, divided by
**	two (becauses there are two).
**
**	The drawing starts from the ceil (res.h = 0, or y = 0) with his own color,
**	stops to the y wall, then the y wall is drawn with the texture color until
**	the y floor is reached & finally the floor is drawn with his own color
**	until the max screen res.h is reached.
**
**	To get the right texture pixel on the wall, we multiply the x_ratio of the
**	x cell hited by the width resolution of the texture, then we multiply the
**	y_ratio of the y wall by the height resolution of texture.
**	For this one there is only one moving variable which is the y wall,
**	therefore, in order to reduce calculations we calculate a pre-ratio before
**	the while instruction which is tex.ratio_y.
**	(ex: if the hit is 33% of the cell, we take the 33% pixel of the x_texture,
**	if we are drawing the 68% piece of wall, we take the 68% piece of y_tex)
*/

void			column_drawing(t_cubfile *cub, double ray, int col_x, int col_y)
{
	t_col		c;
	int			wall_y;
	t_texture	tex;

	if ((c.wall = (int)(cub->cam.d_cam / (0.92 * ray))) > cub->res.h)
		c.wall = cub->res.h;
	c.ceil = (cub->res.h - c.wall) / 2;
	c.floor = (cub->res.h + c.wall) / 2;
	tex.ratio_y = (double)cub->tex[cub->side].h / (double)c.wall;
	wall_y = 0;
	cub->tex_x = (int)(cub->tex_x * cub->tex[cub->side].w);
	while (col_y < c.ceil)
		ft_pixel_put(&(cub->img[0]), col_x, col_y++, cub->colors[1].color);
	while (col_y < c.floor)
	{
		tex.y = (int)(tex.ratio_y * wall_y++);
		tex.color = ((t_color*)cub->tex[cub->side].adr)
			[(int)(cub->tex_x) + (tex.y * cub->tex[cub->side].w)];
		ft_pixel_put(&(cub->img[0]), col_x, col_y++, tex.color.color);
	}
	while (col_y < cub->res.h)
		ft_pixel_put(&(cub->img[0]), col_x, col_y++, cub->colors[0].color);
}

double			raycast(t_cubfile *cub, double angle)
{
	if (angle < 90.0)
		return (rayone(cub->pos.y - floor(cub->pos.y),
				ceil(cub->pos.x) - cub->pos.x, angle * TO_RAD, cub));
	else if (angle < 180.0)
		return (raytwo(cub->pos.y - floor(cub->pos.y),
				cub->pos.x - floor(cub->pos.x), angle * TO_RAD, cub));
	else if (angle < 270.0)
		return (raythree(ceil(cub->pos.y) - cub->pos.y,
				cub->pos.x - floor(cub->pos.x), angle * TO_RAD, cub));
	else
		return (rayfour(ceil(cub->pos.y) - cub->pos.y,
				ceil(cub->pos.x) - cub->pos.x, angle * TO_RAD, cub));
}

/*
**	image_drawing cast rays, one by one, throught the FOV of the player, from
**	the left to the right, & draw the given column of the x screen resolution
**	with it.
*/

void			image_drawing(t_cubfile *cub)
{
	double		ray;
	double		angle;
	double		anglecam;
	int			col_x;

	angle = cub->pos.a + (PLAYER_FOV / 2);
	anglecam = PLAYER_FOV / 2;
	col_x = -1;
	while (++col_x < cub->res.w)
	{
		if (angle < 0.0)
			angle += 360.0;
		else if (angle >= 360.0)
			angle -= 360.0;
		ray = cos(anglecam * TO_RAD) * raycast(cub, angle);
		column_drawing(cub, ray, col_x, 0);
		angle -= cub->cam.angle_gap;
		anglecam -= cub->cam.angle_gap;
	}
}

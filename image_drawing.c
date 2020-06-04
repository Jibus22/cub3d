/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_drawing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 20:27:03 by jle-corr          #+#    #+#             */
/*   Updated: 2020/06/04 13:15:27 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**	column_drawing calculates with the help of the raylen casted & the cam.dcam
**	the lenght of the wall.
**
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
	t_texture	tex;

	c.wall = (int)(cub->cam.d_cam / (0.92 * ray));
	tex.wall_y = c.wall < cub->res.h ? 0 : (c.wall - cub->res.h) / 2;
	tex.ratio_y = (double)cub->tex[cub->side].h / (double)c.wall;
	c.wall = c.wall < cub->res.h ? c.wall : cub->res.h;
	c.ceil = (cub->res.h - c.wall) / 2;
	c.floor = (cub->res.h + c.wall) / 2;
	cub->tex_x = (int)(cub->tex_x * cub->tex[cub->side].w);
	while (col_y < c.ceil)
		ft_pixel_put(&(cub->img[0]), col_x, col_y++, cub->colors[1].color);
	while (col_y < c.floor)
	{
		tex.y = (int)(tex.ratio_y * tex.wall_y++);
		tex.color = ((t_color*)cub->tex[cub->side].adr)
			[(int)(cub->tex_x) + (tex.y * cub->tex[cub->side].w)];
		ft_pixel_put(&(cub->img[0]), col_x, col_y++, tex.color.color);
	}
	while (col_y < cub->res.h)
		ft_pixel_put(&(cub->img[0]), col_x, col_y++, cub->colors[0].color);
}

/*
**	If a new move from the player is recorded, calculations goes on :
**	image_drawing cast rays, one by one, throught the FOV of the player, from
**	the left to the right, & draw the given column of the x screen resolution
**	with it.
**	Finally, move or not, the drawn image is put in the window.
*/

/*
void			sprite_drawing(t_cubfile *cub)
{

}*/

int				image_drawing(t_cubfile *cub)
{
	double		ray;
	double		angle;
	double		anglecam;
	int			col_x;

	if (cub->newmove == 1)
	{
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
		//sprite_drawing(cub);
	}
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->img[0].img, 0, 0);
	cub->newmove = 0;
	return (1);
}

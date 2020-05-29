/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_drawing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 20:27:03 by jle-corr          #+#    #+#             */
/*   Updated: 2020/05/29 22:54:47 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			column_drawing(t_cubfile *cub, double ray, int col)
{
	t_col		c;
	int			e;
	int			pix_wall;
	int			tex_y;
	double		ratio_y;
	t_color		color;

	if ((c.wall = (int)(cub->cam.d_cam / (0.92 * ray))) > cub->res.h)
		c.wall = cub->res.h;//Caclcul de la taille de la colonne a dessiner
	c.ceil = (cub->res.h - c.wall) / 2;//calcul colonne haute (ceil)
	c.floor = (cub->res.h + c.wall) / 2;//calcul colonne basse (floor)
	ratio_y = (double)cub->tex[cub->side].h / (double)c.wall;
	e = 0;
	pix_wall = 0;
	cub->tex_x = (int)(cub->tex_x * cub->tex[cub->side].w);
	while (e < c.ceil)
		ft_pixel_put(&(cub->img[0]), col, e++, cub->colors[1].color);
	while (e < c.floor)
	{
		tex_y = (int)(ratio_y * pix_wall++);
		color =((t_color*)cub->tex[cub->side].adr)[(int)(cub->tex_x) + (tex_y * cub->tex[cub->side].w)];
		ft_pixel_put(&(cub->img[0]), col, e++, color.color);
	}
	while (e < cub->res.h)
		ft_pixel_put(&(cub->img[0]), col, e++, cub->colors[0].color);
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

void			image_drawing(t_cubfile *cub)
{
	double		ray;
	double		angle;
	double		anglecam;
	int			col;

	angle = cub->pos.a + (PLAYER_FOV / 2);
	anglecam = PLAYER_FOV / 2;
	col = -1;
	while (++col < cub->res.w)
	{
		if (angle < 0.0)
			angle += 360.0;
		else if (angle >= 360.0)
			angle -= 360.0;
		ray = cos(anglecam * TO_RAD) * raycast(cub, angle);
		column_drawing(cub, ray, col);
		angle -= cub->cam.angle_gap;
		anglecam -= cub->cam.angle_gap;
	}
}

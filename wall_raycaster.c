/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_raycaster.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 16:38:38 by jle-corr          #+#    #+#             */
/*   Updated: 2020/06/12 15:04:02 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**	rayone, two, three or four each corresponds to a quadrant of the
**	trigonometric circle. One of them is called according to the angle given
**	in parameter.
**	the main process is the same for all.
**
**	There is two rays which are casted : y_grid in a first time, then x_grid.
**
**	We receive the closest y_ray_y or x_ray_x grid in parameter. We first
**	calculate the corresponding y_ray.x or x_ray.y for each of those rays.
**	then we calculate the step xa or ya. their corresponding step in ordinates
**	& abscisses doesn't need calculations cause it is the lenght of a cell = 1.
**
**	then we give back to y_ray_y or x_ray_x their coordinates starting from the
**	player position.
**	Finally, we increment those value y_ray(x & y) & after x_ray(x & y) with
**	their own step values, until we hit a wall cell.
**
**	Before returning the shortest ray, we record the hited side (W,E,N,S) &
**	the x_pos (tex_x) hited, which will be useful to calculate the ratio of
**	the hited cell & by this way give us after the right column texture.
**
**	they only have little differences like the sign of tan()
**	(depending of the angle), the wall side hited or the manner to check the
**	hited cell.
*/

/*
double			cartesian_dist(double xa, double ya, double xb, double yb)
{
	return (sqrt(pow((xb - xa), 2) + pow((yb - ya), 2)));
}*/

// On a tout nos objets set a 0. J'ai un compteur d'objet set à 0.
// Quand je touche un objet, je verifie si il a été initialisé. Si c'est son
// 1er impact, je l'initialise (distance, L x l, col_start) et je met le compteur
// D'objet à 1. -> J'ai 1 objet, à telle distance, qui a pour numéro 0.
// Si cet objet est touché 40 fois, la seule valeur qui changera sera le compteur
// d'impacts (et donc de colonne).
// Si je touche 2 autres objets différents j'aurai mon compteur d'objets à 3 et mes
// objets initialisés de 0 à 2.
// Je pourrai ensuite les trier dans l'ordre décroissant selon leur distance, puis
// les dessiner dans cet ordre.

void			record_sprite(t_cubfile *cub)
{
	cub->newmove = cub->newmove;
}

double			rayone(t_ray *ray, double angle, t_cubfile *cub)
{
	initray_y(ray, cub, angle, 1.0);
	initray_x(ray, cub, angle, -1.0);
	while ((int)ray->y.x < cub->d_map.w &&
			cub->map[(int)(ray->y.y - 0.1)][(int)ray->y.x] != '1')
	{
		if (cub->map[(int)(ray->y.y - 0.1)][(int)ray->y.x] == '2')
			record_sprite(cub);
		ray->y.y -= 1.0;
		ray->y.x += ray->y.xa;
	}
	while ((int)ray->x.y > 0 && (int)ray->x.y < cub->d_map.h &&
			cub->map[(int)ray->x.y][(int)ray->x.x] != '1')
	{
		if (cub->map[(int)(ray->x.y)][(int)ray->x.x] == '2')
			record_sprite(cub);
		ray->x.x += 1.0;
		ray->x.y += ray->x.ya;
	}
	init_raylen_n_side(ray, cub, TX_NO, TX_EA);
	cub->tex_x = ray->y.len < ray->x.len ? ray->y.x -
			(int)ray->y.x : ray->x.y - (int)ray->x.y;
	return (ray->longest_ray);
}

double			raytwo(t_ray *ray, double angle, t_cubfile *cub)
{
	initray_y(ray, cub, angle, 1.0);
	initray_x(ray, cub, angle, 1.0);
	while ((int)ray->y.x > 0 && (int)ray->y.x < cub->d_map.w &&
			cub->map[(int)(ray->y.y - 0.1)][(int)ray->y.x] != '1')
	{
		if (cub->map[(int)(ray->y.y - 0.1)][(int)ray->y.x] == '2')
			record_sprite(cub);
		ray->y.y -= 1.0;
		ray->y.x += ray->y.xa;
	}
	while ((int)ray->x.y > 0 && (int)ray->x.y < cub->d_map.h &&
			cub->map[(int)ray->x.y][(int)(ray->x.x - 0.1)] != '1')
	{
		if (cub->map[(int)(ray->x.y)][(int)(ray->x.x - 0.1)] == '2')
			record_sprite(cub);
		ray->x.x -= 1.0;
		ray->x.y += ray->x.ya;
	}
	init_raylen_n_side(ray, cub, TX_NO, TX_WE);
	cub->tex_x = ray->y.len < ray->x.len ? ray->y.x - (int)ray->y.x :
		ceil(ray->x.y) - ray->x.y;
	return (ray->longest_ray);
}

double			raythree(t_ray *ray, double angle, t_cubfile *cub)
{
	initray_y(ray, cub, angle, -1.0);
	initray_x(ray, cub, angle, 1.0);
	while ((int)ray->y.x > 0 && (int)ray->y.x < cub->d_map.w &&
			cub->map[(int)(ray->y.y)][(int)ray->y.x] != '1')
	{
		if (cub->map[(int)(ray->y.y)][(int)ray->y.x] == '2')
			record_sprite(cub);
		ray->y.y += 1.0;
		ray->y.x += ray->y.xa;
	}
	while ((int)ray->x.y < cub->d_map.h &&
			cub->map[(int)ray->x.y][(int)(ray->x.x - 0.1)] != '1')
	{
		if (cub->map[(int)(ray->x.y)][(int)(ray->x.x - 0.1)] == '2')
			record_sprite(cub);
		ray->x.x -= 1.0;
		ray->x.y += ray->x.ya;
	}
	init_raylen_n_side(ray, cub, TX_SO, TX_WE);
	cub->tex_x = ray->y.len < ray->x.len ? ceil(ray->y.x) - ray->y.x :
		ceil(ray->x.y) - ray->x.y;
	return (ray->longest_ray);
}

double			rayfour(t_ray *ray, double angle, t_cubfile *cub)
{
	initray_y(ray, cub, angle, -1.0);
	initray_x(ray, cub, angle, -1.0);
	while ((int)ray->y.x < cub->d_map.w &&
			cub->map[(int)(ray->y.y)][(int)ray->y.x] != '1')
	{
		if (cub->map[(int)(ray->y.y)][(int)ray->y.x] == '2')
			record_sprite(cub);
		ray->y.y += 1.0;
		ray->y.x += ray->y.xa;
	}
	while ((int)ray->x.y < cub->d_map.h &&
			cub->map[(int)ray->x.y][(int)ray->x.x] != '1')
	{
		if (cub->map[(int)(ray->x.y)][(int)ray->x.x] == '2')
			record_sprite(cub);
		ray->x.x += 1.0;
		ray->x.y += ray->x.ya;
	}
	init_raylen_n_side(ray, cub, TX_SO, TX_EA);
	cub->tex_x = ray->y.len < ray->x.len ? ceil(ray->y.x) - ray->y.x :
		ray->x.y - (int)ray->x.y;
	return (ray->longest_ray);
}

double			raycast(t_cubfile *cub, double angle)
{
	t_ray	ray;

	if (angle < 90.0 && (ray.y.y = cub->pos.y - floor(cub->pos.y)) > -1.0 &&
			(ray.x.x = ceil(cub->pos.x) - cub->pos.x) > -1.0)
		return (rayone(&ray, angle * TO_RAD, cub));
	else if (angle < 180.0 && (ray.y.y = cub->pos.y - floor(cub->pos.y)) > -1.0
			&& (ray.x.x = cub->pos.x - floor(cub->pos.x)) > -1.0)
		return (raytwo(&ray, angle * TO_RAD, cub));
	else if (angle < 270.0 && (ray.y.y = ceil(cub->pos.y) - cub->pos.y) > -1.0
			&& (ray.x.x = cub->pos.x - floor(cub->pos.x)) > -1.0)
		return (raythree(&ray, angle * TO_RAD, cub));
	else
	{
		ray.x.x = ceil(cub->pos.x) - cub->pos.x;
		ray.y.y = ceil(cub->pos.y) - cub->pos.y;
		return (rayfour(&ray, angle * TO_RAD, cub));
	}
}

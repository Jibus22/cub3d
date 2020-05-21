/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_raycaster.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 17:43:14 by jle-corr          #+#    #+#             */
/*   Updated: 2020/05/21 16:43:45 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

/*
** vertic means y ray (which stops every y grid) & horizont means x ray
** (which stops every x grid)
*/

double			rayone(double vertic_y, double horizont_x, double angle, t_cubfile *cub)
{
	double		vertic_x;
	double		vertic_xa;
	double		horizont_y;
	double		horizont_ya;
	double		vertic_ray_len;
	double		horizont_ray_len;

	if ((vertic_x = cub->pos.x + (vertic_y / tan(angle))) > 40000.0)
		vertic_x = 4000.0;
	vertic_xa = 1.0 / tan(angle);
	vertic_y = cub->pos.y - vertic_y;
	while (vertic_x < (double)cub->d_map.w &&
			cub->map[(int)(vertic_y - 0.1)][(int)vertic_x] != '1'
			&& (vertic_y -= 1.0))
		vertic_x += vertic_xa;
	vertic_ray_len = hypot(vertic_x - cub->pos.x, cub->pos.y - vertic_y);
	if ((horizont_y = cub->pos.y - (horizont_x * tan(angle))) < 0.0)
		horizont_y = -4000.0;
	horizont_ya = tan(angle);
	horizont_x += cub->pos.x;
	while ((int)horizont_y > 0 &&
			cub->map[(int)horizont_y][(int)horizont_x] != '1' && (horizont_x += 1.0))
		horizont_y -= horizont_ya;
	horizont_ray_len = hypot(horizont_x - cub->pos.x, cub->pos.y - horizont_y);
	return (vertic_ray_len < horizont_ray_len ? vertic_ray_len : horizont_ray_len);
}

double			raytwo(double vertic_y, double horizont_x, double angle, t_cubfile *cub)
{
	double		vertic_x;
	double		vertic_xa;
	double		horizont_y;
	double		horizont_ya;
	double		vertic_ray_len;
	double		horizont_ray_len;

	if ((vertic_x = cub->pos.x + (vertic_y / tan(angle))) < 0.0)
		vertic_x = -4000.0;
	vertic_xa = 1.0 / tan(angle);
	vertic_y = cub->pos.y - vertic_y;
	while (vertic_x > 0.0 &&
			cub->map[(int)(vertic_y - 0.1)][(int)vertic_x] != '1'
			&& (vertic_y -= 1.0))
		vertic_x += vertic_xa;
	vertic_ray_len = hypot(vertic_x - cub->pos.x, cub->pos.y - vertic_y);
	if ((horizont_y = cub->pos.y + (horizont_x * tan(angle))) < 0.0)
		horizont_y = -4000.0;
	horizont_ya = tan(angle);
	horizont_x = cub->pos.x - horizont_x;
	while ((int)horizont_y > 0.0 &&
			cub->map[(int)horizont_y][(int)(horizont_x - 0.1)] != '1'
			&& (horizont_x -= 1.0))
		horizont_y += horizont_ya;
	horizont_ray_len = hypot(horizont_x - cub->pos.x, cub->pos.y - horizont_y);
	return (vertic_ray_len < horizont_ray_len ? vertic_ray_len : horizont_ray_len);
}

double			raythree(double vertic_y, double horizont_x, double angle, t_cubfile *cub)
{
	double		vertic_x;
	double		vertic_xa;
	double		horizont_y;
	double		horizont_ya;
	double		vertic_ray_len;
	double		horizont_ray_len;

	if ((vertic_x = cub->pos.x - (vertic_y / tan(angle))) < 0.0)
		vertic_x = -4000;;
	vertic_xa = 1.0 / tan(angle);
	vertic_y += cub->pos.y;
	while ((int)vertic_x > 0.0 &&
			cub->map[(int)(vertic_y)][(int)vertic_x] != '1'
			&& (vertic_y += 1.0))
		vertic_x -= vertic_xa;
	vertic_ray_len = hypot(vertic_x - cub->pos.x, cub->pos.y - vertic_y);
	if ((horizont_y = cub->pos.y + (horizont_x * tan(angle))) < 0.0)
		horizont_y = 4000.0;
	horizont_ya = tan(angle);
	horizont_x = cub->pos.x - horizont_x;
	while (horizont_y < (double)cub->d_map.h &&
			cub->map[(int)horizont_y][(int)(horizont_x - 0.1)] != '1'
			&& (horizont_x -= 1.0))
		horizont_y += horizont_ya;
	horizont_ray_len = hypot(horizont_x - cub->pos.x, cub->pos.y - horizont_y);
	return (vertic_ray_len < horizont_ray_len ? vertic_ray_len : horizont_ray_len);
}

double			rayfour(double vertic_y, double horizont_x, double angle, t_cubfile *cub)
{
	double		vertic_x;
	double		vertic_xa;
	double		horizont_y;
	double		horizont_ya;
	double		vertic_ray_len;
	double		horizont_ray_len;

	if ((vertic_x = cub->pos.x + ((vertic_y / tan(angle)) * -1.0)) > 40000.0)
		vertic_x = 40000.0;
	vertic_xa = (1.0 / tan(angle)) * -1.0;
	vertic_y += cub->pos.y;
	while (vertic_x < (double)cub->d_map.w &&
			cub->map[(int)(vertic_y)][(int)vertic_x] != '1'
			&& (vertic_y += 1.0))
		vertic_x += vertic_xa;
	vertic_ray_len = hypot(vertic_x - cub->pos.x, cub->pos.y - vertic_y);
	if ((horizont_y = cub->pos.y + ((horizont_x * tan(angle)) * -1)) > 40000.0
			|| horizont_y < 0.0)
		horizont_y = 40000.0;
	horizont_ya = tan(angle) * -1.0;
	horizont_x += cub->pos.x;
	while (horizont_y < (double)cub->d_map.h &&
			cub->map[(int)horizont_y][(int)horizont_x] != '1'
			&& (horizont_x += 1.0))
		horizont_y += horizont_ya;
	horizont_ray_len = hypot(horizont_x - cub->pos.x, cub->pos.y - horizont_y);
	return (vertic_ray_len < horizont_ray_len ? vertic_ray_len : horizont_ray_len);
}

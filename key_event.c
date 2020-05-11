/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 16:53:41 by jle-corr          #+#    #+#             */
/*   Updated: 2020/05/10 11:48:56 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			get_angle_quarter(t_cubfile *cub, t_dvec *move)
{
	if (move->a < RIGHT_ANGLE)
		cub->quarter = 1;
	else if (move->a < FLAT_ANGLE)
		cub->quarter = 2;
	else if (move->a < THREEQUARTER_ANGLE)
		cub->quarter = 3;
	else if (move->a < CIRCLE_ANGLE)
		cub->quarter = 4;
	else
		cub->quarter = 5;
}

void			rotate_mv(t_cubfile *cub, t_dvec *move, char way)
{
	if (way == 'l')
		move->a += PLAYER_ROTATE;
	else
		move->a -= PLAYER_ROTATE;
	if ((move->a > CIRCLE_A_LOW && move->a < CIRCLE_A_HIH)
			|| (move->a < 0.0000001 && move->a > 0))
		move->a = 0;
	else if (move->a < 0)
		move->a = TWO_H_FORTY_FIVE_A;
	else if (move->a > RIGHT_A_LOW && move->a < RIGHT_A_HIH)
		move->a = RIGHT_ANGLE;
	else if (move->a > FLAT_A_LOW && move->a < FLAT_A_HIH)
		move->a = FLAT_ANGLE;
	else if (move->a > THREEQUARTER_A_LOW && move->a < THREEQUARTER_A_HIH)
		move->a = THREEQUARTER_ANGLE;
	get_angle_quarter(cub, move);
}

void			central_mv(t_dvec *move, char way)
{
	if (way == 'z')
	{
		move->x += 0.5 * cos(move->a);
		move->y -= 0.5 * sin(move->a);
	}
	else
	{
		move->x -= 0.5 * cos(move->a);
		move->y += 0.5 * sin(move->a);
	}
}

void			lateral_mv(t_dvec *move, char way)
{
	if (way == 'q')
	{
		move->x += 0.5 * cos(move->a + M_PI_2);
		move->y -= 0.5 * sin(move->a + M_PI_2);
	}
	else
	{
		move->x -= 0.5 * cos(move->a + M_PI_2);
		move->y += 0.5 * sin(move->a + M_PI_2);
	}
}

int				plyr_move(t_cubfile *cub, char c)
{
	t_dvec		move;

	move = cub->pos;
	if (c == 'l')
		rotate_mv(cub, &move, 'l');
	else if (c == 'r')
		rotate_mv(cub, &move, 'r');
	else if (c == 'z')
		central_mv(&move, 'z');
	else if (c == 's')
		central_mv(&move, 's');
	else if (c == 'q')
		lateral_mv(&move, 'q');
	else if (c == 'd')
		lateral_mv(&move, 'd');
	if ((c = cub->map[(int)(move.y)][(int)(move.x)])
			== '1' || c == '2')
		return (0);
	cub->pos = move;
	return (1);
}

int				key_event(int key, t_cubfile *cub)
{
	if (key == MLXK_Z && (cub->newmove = 1) && !plyr_move(cub, 'z'))
		cub->newmove = 0;
	else if (key == MLXK_S && (cub->newmove = 1) && !plyr_move(cub, 's'))
		cub->newmove = 0;
	else if (key == MLXK_Q && (cub->newmove = 1) && !plyr_move(cub, 'q'))
		cub->newmove = 0;
	else if (key == MLXK_D && (cub->newmove = 1) && !plyr_move(cub, 'd'))
		cub->newmove = 0;
	else if (key == MLXK_LEFT && (cub->newmove = 1) && !plyr_move(cub, 'l'))
		cub->newmove = 0;
	else if (key == MLXK_RIGHT && (cub->newmove = 1) && !plyr_move(cub, 'r'))
		cub->newmove = 0;
	else if (key == MLXK_ESC && (cub->newmove = 1))
		printf("esc key\n");
	else
		return (0);
	return (1);
}

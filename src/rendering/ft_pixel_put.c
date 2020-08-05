/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixel_put.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 13:13:34 by jle-corr          #+#    #+#             */
/*   Updated: 2020/08/05 17:59:50 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			ft_pixel_put(t_img *img, int x, int y, unsigned int color)
{
	*(unsigned int*)(img->adr + ((y * img->size_line) + (x * img->depth / 8))) =
		color;
}

t_color			ft_get_color(t_tex *img, int x, int y)
{
	return (*(t_color*)(img->adr + ((y * img->size_line) +
					(x * img->depth / 8))));
}

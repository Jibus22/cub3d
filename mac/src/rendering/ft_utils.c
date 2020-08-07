/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 13:13:34 by jle-corr          #+#    #+#             */
/*   Updated: 2020/08/06 12:06:22 by jle-corr         ###   ########.fr       */
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

int				ft_error(const char *error)
{
	write(1, "Error:\n", 7);
	write(1, error, ft_strlen(error));
	return (0);
}

char			*ft_strnewspace(int size)
{
	char		*new;

	if (!(new = (char*)malloc(sizeof(*new) * (size += 1))))
		return (NULL);
	new[--size] = 0;
	while (size--)
		new[size] = ' ';
	return (new);
}

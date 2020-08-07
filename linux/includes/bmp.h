/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 17:56:35 by jle-corr          #+#    #+#             */
/*   Updated: 2020/08/06 01:35:25 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

# include "cub3d.h"

/*
** tricky shifty trick : in t_FileHeader, balance variable is only there to
** balance the sum of bytes in the structure, to make it dividable by 4.
** If there is no balance, the structure size will be 14 bytes & the computer
** will automatically add 2 bytes (after signature[2]). This is a problem in
** my save_bmp function, cause I begging to write 14 bytes in the .bmp created
** file, starting from the adress of the first header parameter : signature.
** If no trick is done, signature will be well fullfilled, BUT not ater because
** there will be 2 virtual bytes created by the computer just after them, so
** the 2 first bytes of the unsigned int of the size variable will be skipped,
** and then, everything will be shifted.
*/

typedef struct		s_header_bmpfile
{
	unsigned short	balance;
	unsigned char	signature[2];
	unsigned int	size;
	unsigned short	reserved1;
	unsigned short	reserved2;
	unsigned int	offset;
}					t_fileheader;

typedef struct		s_header_bmpimg
{
	unsigned int	headersize;
	unsigned int	w;
	unsigned int	h;
	unsigned short	plan_nb;
	unsigned short	bpp;
	unsigned int	compression;
	unsigned int	size;
	unsigned int	horizontalres;
	unsigned int	verticalres;
	unsigned int	colornb;
	unsigned int	importantcolors;
}					t_infoheader;

typedef struct		s_bmp
{
	t_fileheader	file_h;
	t_infoheader	info_h;
}					t_bmp;

int					save_bmp(t_cubfile *cub, char *title);

#endif

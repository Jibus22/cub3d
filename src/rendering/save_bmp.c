/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:27:22 by jle-corr          #+#    #+#             */
/*   Updated: 2020/08/06 01:25:05 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp.h"

void			init_bmp_fileheader(t_cubfile *cub, t_bmp *bmp)
{
	bmp->file_h.signature[0] = 'B';
	bmp->file_h.signature[1] = 'M';
	bmp->file_h.size = 54 + (cub->res.w * cub->res.h * 3);
	bmp->file_h.reserved1 = 0;
	bmp->file_h.reserved2 = 0;
	bmp->file_h.offset = 54;
}

void			init_bmp_infoheader(t_cubfile *cub, t_bmp *bmp)
{
	bmp->info_h.headersize = 40;
	bmp->info_h.w = cub->res.w;
	bmp->info_h.h = cub->res.h;
	bmp->info_h.plan_nb = 1;
	bmp->info_h.bpp = 32;
	bmp->info_h.compression = 0;
	bmp->info_h.size = cub->res.w * cub->res.h * 3;
	bmp->info_h.horizontalres = 0;
	bmp->info_h.verticalres = 0;
	bmp->info_h.colornb = 0;
	bmp->info_h.importantcolors = 0;
}

int				save_bmp(t_cubfile *cub, char *title)
{
	t_bmp		bmp;
	int			fd;
	int			bmpsizeline;
	int			y;
	char		*wintitle;

	if (!(wintitle = ft_strjoin(title, ".bmp")))
		return (ft_error("Failed to create the .bmp title"));
	if ((fd = open(wintitle, O_CREAT | O_RDWR, 0644)) < 0)
		return (ft_error("Failed to create the .bmp file"));
	init_bmp_fileheader(cub, &bmp);
	init_bmp_infoheader(cub, &bmp);
	write(fd, &(bmp.file_h.signature), 14);
	write(fd, &(bmp.info_h), 40);
	y = cub->res.h;
	bmpsizeline = cub->res.w * 4;
	while (--y >= 0)
		write(fd, &cub->img[0].adr[y * (cub->img[0].size_line)], bmpsizeline);
	close(fd);
	free(wintitle);
	return (1);
}

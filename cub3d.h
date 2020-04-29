/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 18:15:15 by jle-corr          #+#    #+#             */
/*   Updated: 2020/04/29 16:31:29 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "mlx.h"
# include "libft.h"

# define R	82
# define NO	157
# define SO	162
# define WE	156
# define EA	134
# define S	83
# define F	70
# define C	67

# define W	0
# define H	1
# define O	2

typedef struct	s_gnl
{
	char	*line;
	int		fd;
	int		ret;
	int		nwline;
}				t_gnl;

typedef struct	s_cubfile
{
	int		colors[2][3];
	int		res[2];
	char	*tx_path[6];
	int		nb_elements;
	int		save;
	char	**map;
	int		d_map[2];
	int		map_pos[3];
}				t_cubfile;

/*
**	colors[0 to 1] -> Floor, Ceiling; [0 to 2] -> r, g, b;
**	tx_path[0 to 5] -> NO, SO, WE, EA, S, NULL;
**	d_map[0 to 1] -> W, H;
**	map_pos[0 to 2] -> W, H, Orientation;
*/

int				extract_cub_file(int ac, char **av, t_cubfile *cbfile);
int				handle_map(t_cubfile *cbfile, t_gnl *gnl, char *file);
int				verify_map(char **map);

#endif

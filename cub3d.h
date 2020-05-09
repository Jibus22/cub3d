/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 18:15:15 by jle-corr          #+#    #+#             */
/*   Updated: 2020/05/08 16:57:16 by jle-corr         ###   ########.fr       */
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

# define MLXK_ESC 53
# define MLXK_Z 13
# define MLXK_Q 0
# define MLXK_S 1
# define MLXK_D 2
# define MLXK_LEFT 123
# define MLXK_RIGHT 124

typedef struct		s_gnl
{
	char			*line;
	int				fd;
	int				ret;
	int				nwline;
}					t_gnl;

typedef union		s_color
{
	unsigned int	color;
	struct
	{
		unsigned char		c[3];
		unsigned char		alpha;
	}				rgb;
}					t_color;

typedef struct		s_isqur
{
	int				w;
	int				h;
}					t_isqur;

typedef struct		s_dvector
{
	double			x;
	double			y;
	double			a;
}					t_dvec;

typedef struct		s_cubfile
{
	t_color			colors[2];
	t_isqur			res;
	char			*tx_path[6];
	int				nb_elements;
	int				save;
	int				newmove;
	t_isqur			d_map;
	char			**map;
	t_dvec			pos;
	int				fd;
}					t_cubfile;

/*
**	colors[0 to 1] -> Floor, Ceiling; [0 to 2] -> r, g, b;
**	tx_path[0 to 5] -> NO, SO, WE, EA, S, NULL;
**	d_map[0 to 1] -> W, H;
**	map_pos[0 to 2] -> W, H, Orientation;
*/

typedef struct	s_graphic
{
	void	*mlx_p;
	void	*win_p;
	void	*img_p;
}				t_graphic;

int				extract_cub_file(int ac, char **av, t_cubfile *cbfile);
int				handle_map(t_cubfile *cbfile, t_gnl *gnl, char *file);
int				verify_map(char **map);
int				ft_error(const char *error);
int				key_event(int key, t_cubfile *cub);

#endif

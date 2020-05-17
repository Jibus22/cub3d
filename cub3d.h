/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 18:15:15 by jle-corr          #+#    #+#             */
/*   Updated: 2020/05/17 03:16:45 by jle-corr         ###   ########.fr       */
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

# define PLAYER_ROTATE 10
# define TO_RAD 0.0174532925199432954743716805978692718781530857086181640625
# define DCAM_DIVIDER 1.1547005383792512400731311572599224746227264404296875

typedef struct		s_gnl
{
	char			*line;
	int				fd;
	int				ret;
	int				nwline;
}					t_gnl;

typedef union
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
}					t_dvec;

typedef struct		s_position
{
	double			x;
	double			y;
	double			a;
}					t_pos;

typedef struct	s_img
{
	void	*img;
	char	*adr;
	int		depth;
	int		size_line;
	int		endian;
}				t_img;

typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
}				t_mlx;

typedef struct		s_cam
{
	double			d_cam;
	double			angle_gap;
}					t_cam;

typedef struct		s_dda_ray
{
	t_dvec			raystartx;
	t_dvec			raystarty;
	t_dvec			raystepx;
	t_dvec			raystepy;
	int				hit;
}					t_dda_ray;

typedef struct		s_cubfile
{
	t_color			colors[2];
	t_isqur			res;
	char			*tx_path[6];
	int				nb_elements;
	int				save;
	int				newmove;
	int				alternate;
	double			quarter;
	t_isqur			d_map;
	char			**map;
	t_pos			pos;
	t_mlx			mlx;
	t_img			img[2];
	t_cam			cam;
}					t_cubfile;

/*
**	colors[0 to 1] -> Floor, Ceiling; [0 to 2] -> r, g, b;
**	tx_path[0 to 5] -> NO, SO, WE, EA, S, NULL;
**	d_map[0 to 1] -> W, H;
**	map_pos[0 to 2] -> W, H, Orientation;
*/

int				extract_cub_file(int ac, char **av, t_cubfile *cbfile);
int				handle_map(t_cubfile *cbfile, t_gnl *gnl, char *file);
int				verify_map(char **map);
int				ft_error(const char *error);

int				key_event(int key, t_cubfile *cub);
int				cub_rendering(t_cubfile *cub);
void			image_drawing(t_cubfile *cub);
void			ft_pixel_put(t_img *img, int x, int y, unsigned int color);
t_dvec			x_rayone(double x, double angle, t_cubfile *cub);
t_dvec			x_raytwo(double x, double angle, t_cubfile *cub);
t_dvec			x_raythree(double x, double angle, t_cubfile *cub);
t_dvec			x_rayfour(double x, double angle, t_cubfile *cub);
t_dvec			y_rayone(double y, double angle, t_cubfile *cub);
t_dvec			y_raytwo(double y, double angle, t_cubfile *cub);
t_dvec			y_raythree(double y, double angle, t_cubfile *cub);
t_dvec			y_rayfour(double y, double angle, t_cubfile *cub);

#endif

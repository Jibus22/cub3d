/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 18:15:15 by jle-corr          #+#    #+#             */
/*   Updated: 2020/05/30 17:53:59 by jle-corr         ###   ########.fr       */
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

/*
**	parsing magic numbers
*/

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

/*
**	macosx key controls
*/

# define MLXK_ESC	53
# define MLXK_Z	13
# define MLXK_Q	0
# define MLXK_S	1
# define MLXK_D	2
# define MLXK_LEFT	123
# define MLXK_RIGHT	124

/*
**	player & camera settings
*/

# define PLAYER_FOV	60.0
# define PLAYER_ROTATE	5.0
# define PLAYER_MOVE	0.2
# define TO_RAD	0.0174532925199432954743716805978692718781530857086181640625
# define DCAM_DIVIDER	(2 * tan((PLAYER_FOV / 2) * TO_RAD))

/*
**	texture magic numbers
*/

# define TX_NO	0
# define TX_SO	1
# define TX_WE	2
# define TX_EA	3

/*
**	parsing
*/

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

/*
**	cartesian coordinates
*/

typedef struct		s_isqur
{
	int				w;
	int				h;
}					t_isqur;

typedef struct		s_position
{
	double			x;
	double			y;
	double			a;
}					t_pos;

/*
**	mlx data
*/

typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
}				t_mlx;

typedef struct	s_img
{
	void	*img;
	char	*adr;
	int		depth;
	int		size_line;
	int		endian;
}				t_img;

typedef struct	s_tex_img
{
	void	*img;
	char	*adr;
	int		w;
	int		h;
	int		depth;
	int		size_line;
	int		endian;
}				t_tex;

typedef struct		s_cam
{
	double			d_cam;
	double			angle_gap;
}					t_cam;

/*
**	dda raycasting
*/

typedef struct		s_y_axis
{
	double		x;
	double		xa;
	double		len;
}					t_y_ray;

typedef struct		s_x_axis
{
	double		y;
	double		ya;
	double		len;
}					t_x_ray;

/*
**	column drawing
*/

typedef struct		s_col
{
	int			wall;
	int			ceil;
	int			floor;
}					t_col;

typedef struct		s_texture_xpm
{
	t_color			color;
	double			ratio_y;
	int				y;
}					t_texture;

/*
**	colors[0 to 1] -> Floor, Ceiling; [0 to 2] -> r, g, b;
**	tx_path[0 to 5] -> NO, SO, WE, EA, S, NULL;
*/

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
	int				side;
	double			tex_x;
	t_tex			tex[4];
}					t_cubfile;

/*
**	Extracting .cub data
*/

int				extract_cub_file(int ac, char **av, t_cubfile *cbfile);
int				handle_map(t_cubfile *cbfile, t_gnl *gnl, char *file);
int				verify_map(char **map);
int				ft_error(const char *error);

/*
**	Raycast & rendering
*/

int				key_event(int key, t_cubfile *cub);
int				cub_rendering(t_cubfile *cub);
void			image_drawing(t_cubfile *cub);
void			ft_pixel_put(t_img *img, int x, int y, unsigned int color);
double			rayone(double vertic_y, double horizont_x, double angle, t_cubfile *cub);
double			raytwo(double vertic_y, double horizont_x, double angle, t_cubfile *cub);
double			raythree(double vertic_y, double horizont_x, double angle, t_cubfile *cub);
double			rayfour(double vertic_y, double horizont_x, double angle, t_cubfile *cub);

#endif

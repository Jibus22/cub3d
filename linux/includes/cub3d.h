/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 18:15:15 by jle-corr          #+#    #+#             */
/*   Updated: 2020/08/08 20:18:26 by jle-corr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"

# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

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
**	X11 masks
*/

# define KEYPRESS	2
# define DESTROYNOTIFY	33

/*
**	macosx key controls
*/

# define MLXK_ESC	65307
# define MLXK_Z	122
# define MLXK_Q	113
# define MLXK_S	115
# define MLXK_D	100
# define MLXK_LEFT	65361
# define MLXK_RIGHT	65363

/*
**	player & camera settings
*/

# define PLAYER_FOV	60.0
# define PLAYER_ROTATE	2.8
# define PLAYER_MOVE	0.3
# define PLAYER_LATERAL_MOVE	0.1
# define TO_RAD	0.0174532925199432954743716805978692718781530857086181640625

/*
**	texture magic numbers
*/

# define TX_NO	0
# define TX_SO	1
# define TX_WE	2
# define TX_EA	3
# define TX_SPRITE	4

/*
**	parsing
*/

typedef struct			s_gnl
{
	char				*line;
	int					fd;
	int					ret;
	int					nwline;
}						t_gnl;

typedef union
{
	unsigned int		color;
	struct
	{
		unsigned char	c[3];
		unsigned char	alpha;
	}					rgb;
}						t_color;

/*
**	cartesian coordinates
*/

typedef struct			s_int_square
{
	int					w;
	int					h;
}						t_isqur;

typedef struct			s_position
{
	double				x;
	double				y;
	double				a;
}						t_pos;

/*
**	mlx data
*/

typedef struct			s_mlx
{
	void				*mlx;
	void				*win;
}						t_mlx;

typedef struct			s_img
{
	void				*img;
	char				*adr;
	int					depth;
	int					size_line;
	int					endian;
}						t_img;

typedef struct			s_tex_img
{
	void				*img;
	char				*adr;
	int					w;
	int					h;
	int					depth;
	int					size_line;
	int					endian;
}						t_tex;

typedef struct			s_cam
{
	double				d_cam;
	double				angle_gap;
}						t_cam;

/*
**	dda raycasting
*/

typedef struct			s_y_axis
{
	double				x;
	double				y;
	double				xa;
	double				len;
}						t_y_ray;

typedef struct			s_x_axis
{
	double				x;
	double				y;
	double				ya;
	double				len;
}						t_x_ray;

typedef struct			s_ray
{
	t_x_ray				x;
	t_y_ray				y;
	double				shortest_ray;
}						t_ray;

/*
**	column drawing
*/

typedef struct			s_screenray
{
	double				anglecam;
	double				angle;
	double				ray;
	int					col_x;
}						t_screenray;

typedef struct			s_col
{
	int					wall;
	int					ceil;
	int					floor;
}						t_col;

typedef struct			s_texture_xpm
{
	t_color				color;
	double				ratio_y;
	int					y;
	int					wall_y;
}						t_texture;

/*
**	sprite
*/

typedef struct			s_sprite
{
	t_isqur				cell;
	double				dist;
	double				vx;
	double				vy;
	int					height;
	int					width;
	double				alpha;
	int					mid;
	int					left;
	int					right;
	int					justhited;
	int					firsthit;
	int					lasthit;
}						t_sprite;

typedef struct			s_spritedisplay
{
	double				ratio_x;
	double				ratio_y;
	int					y_start;
	int					y_end;
	int					tex_wall_y;
	int					x_start;
	int					x_end;
	int					tex_wall_x;
}						t_spritedisplay;

/*
**	colors[0 to 1] -> Floor, Ceiling; [0 to 2] -> r, g, b;
**	tx_path[0 to 5] -> NO, SO, WE, EA, S, NULL;
*/

typedef struct			s_cubfile
{
	t_color				colors[2];
	t_isqur				screensize;
	t_isqur				res;
	char				*tx_path[6];
	int					nb_elements;
	int					sprite_nb;
	int					save;
	int					newmove;
	t_isqur				d_map;
	char				**map;
	t_pos				pos;
	t_mlx				mlx;
	t_img				img[1];
	t_cam				cam;
	int					side;
	double				tex_x;
	t_tex				tex[5];
	int					col_x;
	t_sprite			*sprite;
	int					i_sprite;
}						t_cubfile;

/*
**	Extracting .cub data
*/

int						extract_cub_file(int ac, char **av, t_cubfile *cbfile);
int						handle_map(t_cubfile *cbfile, t_gnl *gnl, char *file);
int						verify_map(char **map);

/*
**	Raycast & rendering
*/

int						key_event(int key, t_cubfile *cub);
int						image_drawing(t_cubfile *cub);
int						wall_drawing(t_cubfile *cub);
double					raycast(t_cubfile *cub, double angle, int col_x);
void					initray_y(t_ray *ray, t_cubfile *cub,
						double angle, double sign);
void					initray_x(t_ray *ray, t_cubfile *cub,
						double angle, double sign);
void					init_raylen_n_side(t_ray *ray,
						t_cubfile *cub, int tex_one, int tex_two);

/*
**	Sprites
*/

void					restore_sprite(t_cubfile *cub);
int						record_sprite(t_cubfile *cub, int ycell, int xcell);
void					sprite_drawing(t_cubfile *cub);
int						quit_cub(t_cubfile *cub);

/*
**	Utils
*/

void					ft_pixel_put(t_img *img, int x, int y,
						unsigned int color);
t_color					ft_get_color(t_tex *img, int x, int y);
char					*ft_strnewspace(int size);
int						ft_error(const char *error);
int						ft_errorfree(const char *error, char *str);
void					*create_new_image(t_cubfile *cub, int nb);

#endif

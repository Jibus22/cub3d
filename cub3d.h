/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 18:15:15 by jle-corr          #+#    #+#             */
/*   Updated: 2020/05/10 18:38:55 by jle-corr         ###   ########.fr       */
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

# define PLAYER_ROTATE 0.261799387799149407829446545292739756405353546142578125

# define RIGHT_ANGLE 1.5707963267948965579989817342720925807952880859375
# define RIGHT_A_HIH 1.5707963267948970
# define RIGHT_A_LOW 1.5707963267948960
# define FLAT_ANGLE 3.141592653589793115997963468544185161590576171875
# define FLAT_A_HIH 3.1415926535897940
# define FLAT_A_LOW 3.1415926535897930
# define THREEQUARTER_ANGLE 4.7123889803846896739969452028162777423858642578125
# define THREEQUARTER_A_HIH 4.7123889803846900
# define THREEQUARTER_A_LOW 4.7123889803846890
# define CIRCLE_ANGLE 6.28318530717958623199592693708837032318115234375
# define CIRCLE_A_HIH 6.283185307179590
# define CIRCLE_A_LOW 6.283185307179580
# define TWO_H_FORTY_FIVE_A 6.021385919380435325365397147834300994873046875

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
	double			a;
}					t_dvec;

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
	t_dvec			pos;
	t_mlx			mlx;
	t_img			img[2];
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

#endif

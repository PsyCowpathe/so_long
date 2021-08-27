/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 19:37:36 by agirona           #+#    #+#             */
/*   Updated: 2021/08/27 22:41:11 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx/mlx.h"
# include "libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# define WIN_X 1920
# define WIN_Y 1280
# define GRASS "./texture/grass.xpm"
# define WALL "./texture/wall.xpm"
# define SEED "./texture/mega_seed.xpm"
# define PORTAL "./texture/portal.xpm"
# define CLASSIC "./texture/classic_morty.xpm"
# define OUCH "./texture/ouch_morty.xpm"
# define WALK "./texture/walking_morty.xpm"
# define REV_CLASSIC "./texture/reverse_classic_morty.xpm"
# define REV_OUCH "./texture/reverse_ouch_morty.xpm"
# define REV_WALK "./texture/reverse_walking_morty.xpm"
# define NIMBUS1 "./texture/mr_nimbus1.xpm"
# define NIMBUS2 "./texture/mr_nimbus2.xpm"
# define NIMBUS3 "./texture/mr_nimbus3.xpm"
# define NIMBUS4 "./texture/mr_nimbus4.xpm"
# define NIMBUS5 "./texture/mr_nimbus5.xpm"
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_ECHAP 53

typedef enum	e_error
{
	WIN_ERROR = 1,
	IMG_ERROR = 2,
	XPM_ERROR = 3,
	ARG_ERROR = 4,
	RECT_ERROR = 5,
	CHAR_ERROR = 6,
	END_ERROR = 7,
	SPAWN_ERROR = 8,
	COLLECT_ERROR = 9,
	CLOSE_ERROR = 10,
	NIMB_ERROR = 11,
	MALLOC_ERROR = 12
}				t_error;

typedef struct s_xpm
{
	void	*img;
	int		width;
	int		height;
}				t_xpm;

typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	int		*addr;
	int		bits;
	int		endian;
	int		linelen;
	char	**map;
	int		mapx;
	int		mapy;
	int		px;
	int		py;
	int		forward;
	int		right;
	int		left;
	int		backward;
	int		frame;
	int		moov;
	int		collectible;
	int		count;
	int		jump;
	int		endjump;
	int		direction;
	int		nimbus;
	int		nimbus_frame;
	int		stuck;
	int		time;
	t_xpm	xpm[15];
}				t_mlx;

//physics

int		event(t_mlx *data);

//print_map

void	print_map(t_mlx *data);

//event

int		keypress(int key, t_mlx *data);
int		keyrelease(int key, t_mlx *data);

//utility

void	get_player_pos(t_mlx *data);
int		exit_game(t_mlx *data, int phase);
void	init_struct(t_mlx *data);
int		nb_len(unsigned int	nb);

//mlx_utility

int		init_texture(t_mlx *data);
int		init_mlx(t_mlx *data);
void	clear_window(t_mlx *data);

//parsing

int		get_map(t_mlx *data, char *str);
int		parsing(t_mlx *data);

//error

int		error(int number);

#endif

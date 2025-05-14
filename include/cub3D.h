/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:00:03 by penpalac          #+#    #+#             */
/*   Updated: 2025/05/14 18:11:56 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "libft/include/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

# define WIN_HEIGHT 2048
# define WIN_WIDTH 2048
# define TILE_SIZE 64
# define FOV (M_PI / 3)
# define NUM_RAYS 640
# define TILE_SIZE 64
# define MAX_DEPTH 1000.0

# define K_ESC 65307
# define K_A 97
# define K_D 100
# define K_S 115
# define K_W 119
# define K_AR_R 65363
# define K_AR_L 65361

typedef struct s_paths
{
	char		*N_path;
	char		*S_path;
	char		*W_path;
	char		*E_path;
}				t_paths;

typedef struct s_colors
{
	char		*ceiling;
	char		*floor;
	int			f_r;
	int			f_g;
	int			f_b;
	int			c_r;
	int			c_g;
	int			c_b;
}				t_colors;

typedef struct s_map
{
	t_paths		*paths;
	t_colors	*colors;
	char		**map;
	int			line;
	int			col;
}				t_map;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir;
}				t_player;

typedef struct s_tile
{
	int			x;
	int			y;
	char		*img;
	char		*addr;
	int			bits;
	int			size_line;
	int			endian;
}				t_tile;

typedef struct s_game
{
	t_player	player;
	t_map		*map;

	t_tile		*north;
	t_tile		*south;
	t_tile		*west;
	t_tile		*east;
	t_tile		*frame;

	void		*mlx;
	void		*window;

	int			width;
	int			height;

}				t_game;

/* PARSING */

/* EXECUTION */
void			ft_error(char *str);

void			init_game(t_game *game, t_map *map);
void			start_game(t_game *game, t_map *map);
// void			draw_map(t_game *game, t_map *map);
// void			get_tiles(t_game *game, t_map *map, int x, int y);
int				close_game(t_game *game);

void			assign_images(t_game *game, t_map *map);

int				raycast(t_game *game);
void			calc_distance(double *distance, t_game *game, t_map *map,
					t_player *player, double ray_angle);
double			fix_distortion(double *ray_x, double *ray_y, double player_x,
					double player_y);

int				get_tex_color(t_tile *tex, int x, int y);
t_tile			*get_texture(t_game *game, double ray_x, double ray_y,
					double ray_angle);
void			draw(int wall_top, int wall_bottom, int ray, t_game *game,
					double ray_x, double ray_y, double ray_angle);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:00:03 by penpalac          #+#    #+#             */
/*   Updated: 2025/05/26 18:47:16 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "libft/include/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

# ifndef TILE_SIZE
#  define TILE_SIZE 64
# endif

# define FAIL 0
# define SUCCESS 1

# define K_ESC 65307
# define K_A 97
# define K_D 100
# define K_S 115
# define K_W 119
# define K_AR_R 65363
# define K_AR_L 65361
# define WIN_HEIGHT 540
# define WIN_WIDTH 720
# define TILE_SIZE 64
# define FOV (M_PI / 3)
# define NUM_RAYS WIN_WIDTH
# define MAX_DEPTH 1000.0

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
	char			*n_text;
	char			*s_text;
	char			*w_text;
	char			*e_text;
	char			*f_color;
	char			*c_color;
	int				line;
	int				col;
}					t_map;

typedef struct s_player
{
	double		dir;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
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
	t_player	*player;
	t_map		*map;
	t_tile		*north;
	t_tile		*south;
	t_tile		*west;
	t_tile		*east;
	t_tile		*frame;
	int			*keys;
	void		*mlx;
	void		*window;
	int			width;
	int			height;

}				t_game;

typedef struct s_wall_textures
{
	char			*north;
	char			*south;
	char			*east;
	char			*west;
}					t_wall_textures;

typedef struct s_cub3d
{
	char			**map;
	int				floor_rgb[3];
	int				ceiling_rgb[3];
	char			player_dir;
	int				player_x;
	int				player_y;
	bool			map_started;
	bool			floor_assigned;
	bool			ceiling_assigned;
	t_wall_textures	*wall_textures;
}					t_cub3d;

typedef struct s_ray_cast
{
	double		delta_dist_x;
	double		delta_dist_y;
	double		distance;
	double		side_dist_x;
	double		side_dist_y;
	double		dir_x;
	double		dir_y;
	double		cam_x;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	double		angle_step;
	int			x;
	int			hit;
	int			side;
	int			ray;
	double		ray_x;
	double		ray_y;
	double		ray_angle;
	double		dx;
	double		dy;
}				t_ray_cast;

/*  PARSING */
int					file_validation(char *map_file, t_cub3d *cub3d);
int	                ft_validate_texture_line(char *line, int i, char flag,
		                t_cub3d *cub3d);
int             	ft_validate_color_line(char *line, int i, char flag,
		                t_cub3d *cub3d);
int					ft_check_map_extensions(char *map_file_name,
						char *extension);
int					ft_store_map_lines(int fd, char *first_line,
						t_cub3d *cub3d);
int					ft_map_validation(t_cub3d *cub3d);
int					ft_check_map_closed(t_cub3d *cub3d);

char				*ft_strip_newline(char *str);

/*  ERROR_HANDLING  */
void				ft_error(const char *error_msg);
void				ft_error_exit(const char *error_msg);

/* EXECUTION */

void			init_game(t_game *game, t_map *map);
void			start_game(t_game *game, t_map *map);
int				close_game(t_game *game);

void			assign_images(t_game *game, t_map *map);

int				raycast(t_game *game);

void			calculate_distance(t_ray_cast *rc, t_game *game);
void			put_pixel_frame(t_tile *frame, int x, int y, int color);
t_tile			*get_texture(t_game *game, int side, double ray_angle);
void			draw(int wall_top, int wall_bottom, t_ray_cast *rc,
					t_game *game);

int				key_input(int keycode, t_game *game);
int				loop_hook(t_game *game);
int				key_release(int keycode, t_game *game);
int				key_press(int keycode, t_game *game);

#endif

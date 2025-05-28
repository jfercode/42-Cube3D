/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:00:03 by penpalac          #+#    #+#             */
/*   Updated: 2025/05/28 17:36:05 by jaferna2         ###   ########.fr       */
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

# define SPEED 1
# define ROT_SPEED 0.01

typedef struct s_keys 
{
	int w;
	int s;
	int a;
	int d;
	int left;
	int right;
}	t_keys;

typedef struct s_player
{
	double		dir;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		wall_x;
	double		wall_y;
	t_keys		*keys;
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

typedef struct s_wall_textures
{
	char			*north;
	char			*south;
	char			*east;
	char			*west;
}					t_wall_textures;

typedef struct s_cub3d
{
	int				floor_rgb[3];
	int				ceiling_rgb[3];
	char			player_dir;
	int				player_x;
	int				player_y;
	bool			map_started;
	bool			floor_assigned;
	bool			ceiling_assigned;
	t_wall_textures	*wall_textures;
	char			**map;
}					t_cub3d;

typedef struct s_game
{
	t_cub3d		*cub3d;
	t_player	*player;
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
void				ft_print_cub3d(t_cub3d *cub3d);
void				ft_free_cub3d(t_cub3d *cub3d);

int					ft_file_validation(char *map_file, t_cub3d *cub3d);
int					ft_validate_texture_line(char *line, int i, char flag,
						t_cub3d *cub3d);
int					ft_validate_color_line(char *line, int i, char flag,
						t_cub3d *cub3d);
int					ft_check_file_extensions(char *map_file_name,
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

void			init_game(t_game *game, t_cub3d *cub3d);
void			start_game(t_game *game);
int				close_game(t_game *game);

void		    update_player(t_game *game);
void			rotate(t_game *game, double angle);
void			movement(t_game *game, double x, double y);

void			assign_images(t_game *game);

int				raycast(t_game *game);

void			calculate_distance(t_ray_cast *rc, t_game *game);
void			put_pixel_frame(t_tile *frame, int x, int y, int color);
t_tile			*get_texture(t_game *game, int side, double ray_angle);
void			draw(int wall_top, int wall_bottom, t_ray_cast *rc,
					t_game *game);

int				loop_hook(t_game *game);
int				key_release(int keycode, t_game *game);
int				key_press(int keycode, t_game *game);

#endif

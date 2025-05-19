/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:00:03 by penpalac          #+#    #+#             */
/*   Updated: 2025/05/19 19:23:06 by jaferna2         ###   ########.fr       */
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

typedef struct s_game
{
	void			*mlx;
	void			*window;

	int				win_wid;
	int				win_len;

	t_img			*north;
	t_img			*south;
	t_img			*west;
	t_img			*east;

}					t_game;

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

/*  PARSING */
void				ft_print_cub3d(t_cub3d *cub3d);
void				ft_free_cub3d(t_cub3d *cub3d);

int					ft_file_validation(char *map_file, t_cub3d *cub3d);
int	                ft_validate_texture_line(char *line, int i, char flag,
		                t_cub3d *cub3d);
int             	ft_validate_color_line(char *line, int i, char flag,
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

#endif

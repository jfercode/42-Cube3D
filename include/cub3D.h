/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:00:03 by penpalac          #+#    #+#             */
/*   Updated: 2025/05/12 19:35:22 by penpalac         ###   ########.fr       */
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

# define K_ESC 65307
# define K_A 97
# define K_D 100
# define K_S 115
# define K_W 119
# define K_AR_R 65363
# define K_AR_L 65361

typedef struct s_paths
{
	char	*N_text;
	char	*S_text;
	char	*W_text;
	char	*E_text;
}			t_paths;

typedef struct s_colors
{
	char	*ceiling;
	char	*floor;
	int		f_r;
	int		f_g;
	int		f_b;
	int		c_r;
	int		c_g;
	int		c_b;
}			t_colors;

typedef struct s_map
{
	t_paths     *paths;
    t_colors    *colors;
    char        **map;
    int         line;
    int         col;
}			t_map;

typedef struct s_game
{
	void	*mlx;
	void	*window;

	int		win_wid;
	int		win_len;

	t_img	*north;
	t_img	*south;
	t_img	*west;
	t_img	*east;

}			t_game;

/* PARSING */

/* EXECUTION */

#endif
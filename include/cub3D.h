/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:00:03 by penpalac          #+#    #+#             */
/*   Updated: 2025/05/12 19:17:26 by penpalac         ###   ########.fr       */
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

typedef struct s_map
{
    char    *N_text;
    char    *S_text;
    char    *W_text;
    char    *E_text;
    char    *F_color;
    char    *C_color;
    int     line;
    int     col;
}			t_map;

typedef struct s_game
{
	void	*mlx;
	void	*window;

	int		win_wid;
	int		win_len;

    t_img   *north;
    t_img   *south;
    t_img   *west;
    t_img   *east;

}			t_game;

#endif
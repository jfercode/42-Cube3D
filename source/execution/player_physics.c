/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_physics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:31:05 by jaferna2          #+#    #+#             */
/*   Updated: 2025/05/28 18:27:08 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	movement(t_game *game, double x, double y)
{
	int		next_tile;
	int		next_x;
	int		next_y;
	double	new_x;
	double	new_y;

	new_x = game->player->pos_x + x;
	new_y = game->player->pos_y + y;
	next_x = (int)(new_x / TILE_SIZE);
	next_y = (int)(new_y  / TILE_SIZE);
    
	if (next_x >= 0 && next_x < game->width && next_y >= 0
		&& next_y < game->height)
	{
		next_tile = game->cub3d->map[next_y][next_x];
		if (next_tile != '1' && new_y <= next_y * (TILE_SIZE / 0.5)
            && new_y >= next_y * (TILE_SIZE  * 0.5)
            && new_x <= next_x * (TILE_SIZE  / 0.5)
            && new_x >= next_x * (TILE_SIZE  * 0.5))
		{
            printf("new x %f, y %f   next x %d, y %d\n", new_x, new_y, next_x, next_y);
            game->player->pos_x = new_x;
            game->player->pos_y = new_y;
		}
	}
}

// void movement(t_game *game, double x, double y)
// {
// 	double	new_x = game->player->pos_x + x;
// 	double	new_y = game->player->pos_y + y;
// 	double	pos_x = game->player->pos_x;
// 	double	pos_y = game->player->pos_y;

// 	// Movimiento en X si no colisiona
// 	int next_tile_x = game->cub3d->map[(int)(pos_y / TILE_SIZE)][(int)(new_x / TILE_SIZE)];
// 	if (next_tile_x != '1')
// 		game->player->pos_x = new_x;

// 	// Movimiento en Y si no colisiona
// 	int next_tile_y = game->cub3d->map[(int)(new_y / TILE_SIZE)][(int)(pos_x / TILE_SIZE)];
// 	if (next_tile_y != '1')
// 		game->player->pos_y = new_y;

// 	printf("new x %f, y %f   next tile x %c, tile y %c\n",
// 		game->player->pos_x, game->player->pos_y,
// 		next_tile_x, next_tile_y);
// }

void	rotate(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player->dir_x;
	old_plane_x = game->player->plane_x;
	game->player->dir_x = game->player->dir_x * cos(angle) - game->player->dir_y
		* sin(angle);
	game->player->dir_y = game->player->dir_y = old_dir_x * sin(angle)
		+ game->player->dir_y * cos(angle);
	game->player->plane_x = game->player->plane_x * cos(angle)
		- game->player->plane_y * sin(angle);
	game->player->plane_y = old_plane_x * sin(angle) + game->player->plane_y
		* cos(angle);
	game->player->dir = atan2(game->player->dir_y, game->player->dir_x);
}


void    update_player(t_game *game)
{
    if (game->player->keys->w)
	    movement(game, game->player->dir_x * SPEED, game->player->dir_y
		    * SPEED);
    else if (game->player->keys->d)
	    movement(game, -game->player->dir_y * SPEED, game->player->dir_x
		    * SPEED);
    else if (game->player->keys->s)
	    movement(game, -game->player->dir_x * SPEED, -game->player->dir_y
		    * SPEED);
    else if (game->player->keys->a)
	    movement(game, game->player->dir_y * SPEED, -game->player->dir_x
		    * SPEED);
    else if (game->player->keys->left)
	    rotate(game, -ROT_SPEED);
    else if (game->player->keys->right)
	    rotate(game, ROT_SPEED);
}
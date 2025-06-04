/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_physics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:31:05 by jaferna2          #+#    #+#             */
/*   Updated: 2025/06/04 18:30:50 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	movement(t_game *game, double x, double y)
{
	double	new_x;
	double	new_y;

	new_x = game->player->pos_x + x;
	new_y = game->player->pos_y + y;
	if (game->cub3d->map[(int)(game->player->pos_y / TILE_SIZE)][(int)((new_x
				+ OFFSET) / TILE_SIZE)] != '1'
		&& game->cub3d->map[(int)(game->player->pos_y / TILE_SIZE)][(int)((new_x
				- OFFSET) / TILE_SIZE)] != '1')
	{
		game->player->pos_x = new_x;
	}
	if (game->cub3d->map[(int)((new_y + OFFSET)
			/ TILE_SIZE)][(int)(game->player->pos_x / TILE_SIZE)] != '1'
		&& game->cub3d->map[(int)((new_y - OFFSET)
			/ TILE_SIZE)][(int)(game->player->pos_x / TILE_SIZE)] != '1')
	{
		game->player->pos_y = new_y;
	}
}

void	rotate(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player->dir_x;
	old_plane_x = game->player->plane_x;
	game->player->dir_x = game->player->dir_x * cos(angle) - game->player->dir_y
		* sin(angle);
	game->player->dir_y = old_dir_x * sin(angle)
		+ game->player->dir_y * cos(angle);
	game->player->plane_x = game->player->plane_x * cos(angle)
		- game->player->plane_y * sin(angle);
	game->player->plane_y = old_plane_x * sin(angle) + game->player->plane_y
		* cos(angle);
	game->player->dir = atan2(game->player->dir_y, game->player->dir_x);
}

void	update_player(t_game *game)
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

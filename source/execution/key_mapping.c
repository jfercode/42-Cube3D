/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mapping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:06:08 by penpalac          #+#    #+#             */
/*   Updated: 2025/05/27 16:45:27 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	movement(t_game *game, double x, double y)
{
	int		next_tile;
	int		next_x;
	int		next_y;
	double	new_x;
	double	new_y;

	new_x = game->player->pos_x + x;
	new_y = game->player->pos_y + y;
	next_x = (int)(new_x / TILE_SIZE);
	next_y = (int)(new_y / TILE_SIZE);
	if (next_x >= 0 && next_x < game->width && next_y >= 0
		&& next_y < game->height)
	{
		next_tile = game->cub3d->map[next_y][next_x];
		if (next_tile != '1')
		{
			game->player->pos_x = new_x;
			game->player->pos_y = new_y;
		}
	}
}

static void	rotate(t_game *game, double angle)
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

int	key_input(int keycode, t_game *game)
{
	if (keycode == K_ESC)
		close_game(game);
	else
	{
		if (keycode == K_W)
			movement(game, game->player->dir_x * SPEED, game->player->dir_y
				* SPEED);
		else if (keycode == K_D)
			movement(game, -game->player->dir_y * SPEED, game->player->dir_x
				* SPEED);
		else if (keycode == K_S)
			movement(game, -game->player->dir_x * SPEED, -game->player->dir_y
				* SPEED);
		else if (keycode == K_A)
			movement(game, game->player->dir_y * SPEED, -game->player->dir_x
				* SPEED);
		else if (keycode == K_AR_L)
			rotate(game, -ROT_SPEED);
		else if (keycode == K_AR_R)
			rotate(game, ROT_SPEED);
		raycast(game);
	}
	return (0);
}

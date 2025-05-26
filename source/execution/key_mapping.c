/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mapping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:06:08 by penpalac          #+#    #+#             */
/*   Updated: 2025/05/26 19:16:33 by penpalac         ###   ########.fr       */
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
	next_y = (int)(new_y / TILE_SIZE);
	if (next_x >= 0 && next_x < game->width && next_y >= 0
		&& next_y < game->height)
	{
		next_tile = game->cub3d->map[next_y][next_x];
		if (next_tile != '1')
		{
			game->player->pos_x = new_x;
			game->player->pos_y = new_y;
			raycast(game);
		}
	}
}

int	key_input(int keycode, t_game *game)
{
	if (keycode == K_ESC)
		close_game(game);
	else if (keycode == K_W)
		movement(game, 0, TILE_SIZE);
	else if (keycode == K_A)
		movement(game, TILE_SIZE, 0);
	else if (keycode == K_S)
		movement(game, 0, -TILE_SIZE);
	else if (keycode == K_D)
		movement(game, -TILE_SIZE, 0);
	else if (keycode == K_AR_L)
	{
		game->player->dir = game->player->dir + (-TILE_SIZE / 2);
		raycast(game);
	}
	else if (keycode == K_AR_R)
	{
		game->player->dir = game->player->dir + (TILE_SIZE / 2);
		raycast(game);	
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mapping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:06:08 by penpalac          #+#    #+#             */
/*   Updated: 2025/05/26 18:39:35 by penpalac         ###   ########.fr       */
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

	printf("Player position: (%f, %f)\n", game->player->pos_x,
		game->player->pos_y);
	new_x = game->player->pos_x + x;
	new_y = game->player->pos_y + y;
	next_x = (int)(new_x / TILE_SIZE);
	next_y = (int)(new_y / TILE_SIZE);
	printf("Next indices: (%d, %d)\n", next_x, next_y);
	if (next_x >= 0 && next_x < game->map->width && next_y >= 0
		&& next_y < game->map->height)
	{
		next_tile = game->map->map[next_y][next_x];
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

int key_press(int keycode, t_game *game)
{
    if (keycode < 256)
        game->keys[keycode] = 1;
    if (keycode == K_ESC)
        exit(0);
    return 0;
}
int key_release(int keycode, t_game *game)
{
    if (keycode < 256)
        game->keys[keycode] = 0;
    return 0;
}
int loop_hook(t_game *game)
{
    if (game->keys[4])
        movement(game, 0, -1); // Cambia según tu lógica de movimiento
    if (game->keys[1])
        movement(game, -1, 0);
    if (game->keys[3])
        movement(game, 0, 1);
    if (game->keys[2])
        movement(game, 1, 0);
    // Aquí también puedes hacer raycast, render, etc.
    return 0;
}


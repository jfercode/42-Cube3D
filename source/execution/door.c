/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:19:56 by penpalac          #+#    #+#             */
/*   Updated: 2025/07/01 17:53:02 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	door_close(t_game *game)
{
	game->cub3d->door_timer--;
	if (game->cub3d->door_timer == 0)
	{
		if ((int)(game->player->pos_x / TILE_SIZE) != game->cub3d->door_x
			|| (int)(game->player->pos_y / TILE_SIZE) != game->cub3d->door_y)
		{
			game->cub3d->map[game->cub3d->door_y][game->cub3d->door_x] = 'D';
		}
	}
}

int	update_loop(t_game *game)
{
	static int	cont = 0;

	if (game->cub3d->door_anim == 1)
	{
		if (game->cub3d->door_frame < 4)
		{
			if (cont >= 30)
			{
				game->cub3d->door_frame++;
				cont = 0;
			}
			cont++;
		}
	}
	if (game->cub3d->door_frame == 4)
	{
		game->cub3d->door_anim = 0;
		game->cub3d->door_frame = 0;
		cont = 0;
		game->cub3d->map[game->cub3d->door_y][game->cub3d->door_x] = '0';
		game->cub3d->door_timer = 600;
	}
	if (game->cub3d->door_timer > 0)
		door_close(game);
	return (1);
}

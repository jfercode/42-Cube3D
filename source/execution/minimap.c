/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:15:45 by penpalac          #+#    #+#             */
/*   Updated: 2025/06/04 19:40:43 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	put_minimap_onscreen(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	x = x * 10;
	y = y * 10;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			put_pixel_frame(game->frame, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

static void	draw_square(t_game *game, int start_x, int start_y, int end_x,
		int end_y)
{
	int	i;
	int	j;
	int	color;

	i = start_y;
	while (i <= end_y)
	{
		j = start_x;
		while (j <= end_x)
		{
			if (j >= 0 && j <= game->width && i >= 0 && i <= game->height)
			{
				if (game->cub3d->map[i][j] == '1')
					color = 0x000000;
				else if (i == (int)(game->player->pos_y / TILE_SIZE)
					&& j == (int)(game->player->pos_x / TILE_SIZE))
					color = 0xFF00FF;
				else
					color = 0xFFFFFF;
			}
			put_minimap_onscreen(game, j - start_x, i - start_y, color);
			j++;
		}
		i++;
	}
}

static void	draw_base(t_game *game)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i <= 10)
	{
		j = 0;
		while (j <= 10)
		{
			color = 0x000000;
			put_minimap_onscreen(game, j, i, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;

	draw_base(game);
	start_x = (int)(game->player->pos_x / TILE_SIZE) - 5;
	if (start_x < 0)
		start_x = 0;
	start_y = (int)(game->player->pos_y / TILE_SIZE) - 5;
	if (start_y < 0)
		start_y = 0;
	end_x = (int)(game->player->pos_x / TILE_SIZE) + 5;
	if (end_x >= game->width)
		end_x = game->width - 1;
	end_y = (int)(game->player->pos_y / TILE_SIZE) + 5;
	if (end_y >= game->height)
		end_y = game->height - 1;
	draw_square(game, start_x, start_y, end_x, end_y);
}

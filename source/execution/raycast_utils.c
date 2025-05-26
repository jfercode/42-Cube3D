/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:45:53 by penpalac          #+#    #+#             */
/*   Updated: 2025/05/26 17:54:29 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void get_dist_and_step(t_ray_cast *rc, t_game *game)
{
	if (rc->dir_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (game->player->pos_x - rc->map_x * TILE_SIZE)
			* rc->delta_dist_x / TILE_SIZE;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = ((rc->map_x + 1) * TILE_SIZE - game->player->pos_x)
			* rc->delta_dist_x / TILE_SIZE;
	}
	if (rc->dir_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (game->player->pos_y - rc->map_y * TILE_SIZE)
			* rc->delta_dist_y / TILE_SIZE;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = ((rc->map_y + 1) * TILE_SIZE - game->player->pos_y)
			* rc->delta_dist_y / TILE_SIZE;
	}
}

static void	get_side(t_ray_cast *rc, t_game *game)
{
	rc->hit = 0;
	while (!rc->hit)
	{
		if (rc->side_dist_x < rc->side_dist_y)
		{
			rc->side_dist_x += rc->delta_dist_x;
			rc->map_x += rc->step_x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->map_y += rc->step_y;
			rc->side = 1;
		}
		if (rc->map_y < 0 || rc->map_y >= game->map->height || rc->map_x < 0
			|| rc->map_x >= game->map->width)
			break ;
		if (game->map->map[rc->map_y][rc->map_x] == '1')
			rc->hit = 1;
	}
}

void	calculate_distance(t_ray_cast *rc, t_game *game)
{
	rc->map_x = (int)(game->player->pos_x / TILE_SIZE);
	rc->map_y = (int)(game->player->pos_y / TILE_SIZE);
	rc->dir_x = cos(rc->ray_angle);
	rc->dir_y = sin(rc->ray_angle);
	rc->delta_dist_x = fabs(1 / rc->dir_x);
	rc->delta_dist_y = fabs(1 / rc->dir_y);
	get_dist_and_step(rc, game);
	get_side(rc, game);
	if (rc->side == 0)
		rc->distance = ((rc->map_x * TILE_SIZE - game->player->pos_x) + (1 - rc->step_x) * TILE_SIZE / 2)\
			/ rc->dir_x;
	else
		rc->distance = ((rc->map_y * TILE_SIZE - game->player->pos_y) + (1 - rc->step_y) * TILE_SIZE / 2)\
			/ rc->dir_y;
	rc->ray_x = game->player->pos_x + rc->dir_x * rc->distance;
	rc->ray_y = game->player->pos_y + rc->dir_y * rc->distance;
}

t_tile	*get_texture(t_game *game, int side, double ray_angle)
{
	if (side == 1)
	{
		if (sin(ray_angle) > 0)
			return (game->south);
		else
			return (game->north);
	}
	else
	{
		if (cos(ray_angle) > 0)
			return (game->east);
		else
			return (game->west);
	}
}

void	put_pixel_frame(t_tile *frame, int x, int y, int color)
{
	char	*text;

	if (x < 0 || y < 0 || x >= frame->x || y >= frame->y)
		return ;
	text = frame->addr + (y * frame->size_line + x * (frame->bits / 8));
	*(unsigned int *)text = color;
}

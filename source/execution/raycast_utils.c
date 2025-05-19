/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:45:53 by penpalac          #+#    #+#             */
/*   Updated: 2025/05/19 14:04:37 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// double	fix_distortion(double *ray_x, double *ray_y, double player_x,
// 		double player_y)
// {
// 	corrected_distance = distance * cos(ray_angle - player->dir);
// 	if (corrected_distance < 0.1)
// 		corrected_distance = 0.1;
// 	return (distance);
// }

void	calc_distance(t_ray_cast *rc, t_game *game)
{
	while (rc->distance < MAX_DEPTH && !rc->hit)
	{
		rc->ray_x = game->player.x + cos(rc->ray_angle) * rc->distance;
		rc->ray_y = game->player.y + sin(rc->ray_angle) * rc->distance;
		rc->map_x = (int)(rc->ray_x / TILE_SIZE);
		rc->map_y = (int)(rc->ray_y / TILE_SIZE);
		if (rc->map_y < 0 || rc->map_y >= game->map->col || rc->map_x < 0
			|| rc->map_x >= game->map->line)
			break ;
		if (game->map->map[rc->map_y][rc->map_x] == '1')
		{
			rc->hit = 1;
			rc->delta_dist_x = fabs(game->player.x - rc->ray_x);
			rc->delta_dist_y = fabs(game->player.y - rc->ray_y);
			if (rc->delta_dist_x > rc->delta_dist_y)
				rc->side = 0;
			else
				rc->side = 1;
		}
		rc->distance += 1;
	}
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
	char	*dst;

	if (x < 0 || y < 0 || x >= frame->x || y >= frame->y)
		return ;
	dst = frame->addr + (y * frame->size_line + x * (frame->bits / 8));
	*(unsigned int *)dst = color;
}

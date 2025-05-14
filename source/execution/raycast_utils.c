/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:45:53 by penpalac          #+#    #+#             */
/*   Updated: 2025/05/14 17:42:34 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

double	fix_distortion(double *ray_x, double *ray_y, double player_x,
		double player_y)
{
	double	distance;
	double	dx;
	double	dy;

	dx = *ray_x - player_x;
	dy = *ray_y - player_y;
	distance = sqrt(dx * dx + dy * dy);
	if (distance > 0)
	{
		*ray_x = player_x + (dx / distance) * TILE_SIZE;
		*ray_y = player_y + (dy / distance) * TILE_SIZE;
	}
	// corrected_distance = distance * cos(ray_angle - player->dir);
	// if (corrected_distance < 0.1)
	// 	corrected_distance = 0.1;
	return (distance);
}

void	calc_distance(double *distance, t_game *game, t_map *map,
		t_player *player, double ray_angle)
{
	double	ray_x;
	double	ray_y;
	int		map_y;
	int		map_x;

	while (*distance < MAX_DEPTH) // this is infinite for some reason
	{
		ray_x = player->x + cos(ray_angle) * *distance;
		ray_y = player->y + sin(ray_angle) * *distance;
		map_x = (int)(ray_x / TILE_SIZE);
		map_y = (int)(ray_y / TILE_SIZE);
		if (map_y < 0 || map_y >= map->col || map_x < 0
			|| map_x >= map->line)
			break ;
		if (map->map[map_y][map_x] == '1')
			break ;
		*distance += 1.0;
	}
}

int	get_tex_color(t_tile *tex, int x, int y)
{
	int		offset;
	char	*pixel;

	offset = (y * tex->size_line) + (x * (tex->bits / 8));
	pixel = tex->addr + offset;
	return (*(unsigned int *)pixel);
}

t_tile	*get_texture(t_game *game, double ray_x, double ray_y, double ray_angle)
{
	t_tile	*texture;
	double	x_hit;
	double	y_hit;

	x_hit = fmod(ray_x, TILE_SIZE);
	y_hit = fmod(ray_y, TILE_SIZE);
	if (x_hit < 0)
		x_hit += TILE_SIZE;
	if (y_hit < 0)
		y_hit += TILE_SIZE;
	if (x_hit < 0.001 || x_hit > TILE_SIZE - 0.001)
	{
		if (cos(ray_angle) > 0)
			texture = game->east;
		else
			texture = game->west;
	}
	else
	{
		if (sin(ray_angle) > 0)
			texture = game->south;
		else
			texture = game->north;
	}
	return (texture);
}

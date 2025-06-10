/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:06:42 by penpalac          #+#    #+#             */
/*   Updated: 2025/06/10 16:37:36 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	get_wall_height(t_game *game, t_ray_cast *rc, double corrected_dist)
{
	double	wall_height;
	int		wall_bottom;
	int		wall_top;

	wall_height = (TILE_SIZE * WIN_HEIGHT) / corrected_dist;
	if (wall_height > WIN_HEIGHT)
		wall_height = WIN_HEIGHT;
	wall_top = (WIN_HEIGHT / 2) - (wall_height / 2);
	wall_bottom = wall_top + wall_height;
	draw(wall_top, wall_bottom, rc, game);
}

int	raycast(t_game *game)
{
	t_ray_cast	*rc;
	double		corrected_dist;

	rc = ft_calloc(sizeof(t_ray_cast), 1);
	if (!rc)
		ft_error("Calloc on ray_cast");
	rc->ray = 0;
	rc->angle_step = (M_PI / 3) / NUM_RAYS;
	rc->ray_angle = game->player->dir - ((M_PI / 3) / 2);
	while (rc->ray < NUM_RAYS)
	{
		rc->hit = 0;
		rc->distance = 0;
		calculate_distance(rc, game);
		corrected_dist = rc->distance * cos(rc->ray_angle - game->player->dir);
		if (corrected_dist < 0.1)
			corrected_dist = 0.1;
		get_wall_height(game, rc, corrected_dist);
		rc->ray_angle += rc->angle_step;
		rc->ray++;
	}
	if (IS_BONUS == 1)
		draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->window, game->frame->img, 0, 0);
	free(rc);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:06:42 by penpalac          #+#    #+#             */
/*   Updated: 2025/05/19 14:07:38 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	draw_ceilin_and_floor(int wall_top, int wall_bottom, \
	t_ray_cast *rc, t_game *game)
{
	int	i;

	i = 0;
	while (i < wall_top)
	{
		put_pixel_frame(game->frame, rc->ray, i, 0x69B00B);
		i++;
	}
	i = wall_bottom;
	while (i < game->height)
	{
		put_pixel_frame(game->frame, rc->ray, i, 0x420536);
		i++;
	}
}

void	draw(int wall_top, int wall_bottom, t_ray_cast *rc, t_game *game)
{
	t_tile	*texture;
	int		tex_x;
	int		tex_y;
	int		color;
	int		i;

	texture = get_texture(game, rc->side, rc->ray_angle);
	if (texture == game->north || texture == game->south)
		tex_x = (int)(rc->ray_x) % TILE_SIZE;
	else
		tex_x = (int)(rc->ray_y) % TILE_SIZE;
	tex_x = (tex_x * texture->x) / TILE_SIZE;
	draw_ceilin_and_floor(wall_top, wall_bottom, rc, game);
	i = wall_top;
	while (i < wall_bottom)
	{
		tex_y = ((i - wall_top) * texture->y) / (wall_bottom - wall_top);
		color = *(int *)(texture->addr + tex_y * texture->size_line + tex_x\
           * (texture->bits / 8));
		put_pixel_frame(game->frame, rc->ray, i, color);
		i++;
	}
}

int	raycast(t_game *game)
{
	t_ray_cast	*rc;
	double		wall_height;
	int			wall_bottom;
	int			wall_top;
	double		corrected_dist;

	rc = ft_calloc(sizeof(t_ray_cast), 1);
	if (!rc)
		ft_error("Calloc on ray_cast");
	rc->angle_step = FOV / NUM_RAYS;
	rc->ray_angle = game->player.dir - (FOV / 2);
	rc->ray = 0;
	while (rc->ray < NUM_RAYS)
	{
		rc->hit = 0;
		rc->distance = 0;
		calc_distance(rc, game);
		corrected_dist = rc->distance * cos(rc->ray_angle - game->player.dir);
		if (corrected_dist < 0.1)
			corrected_dist = 0.1;
		wall_height = (TILE_SIZE * game->height) / corrected_dist;
		if (wall_height > game->height)
			wall_height = game->height;
		wall_top = (game->height / 2) - (wall_height / 2);
		wall_bottom = wall_top + wall_height;
		draw(wall_top, wall_bottom, rc, game);
		rc->ray_angle += rc->angle_step;
		rc->ray++;
	}
	mlx_put_image_to_window(game->mlx, game->window, game->frame->img, 0, 0);
	return (0);
}

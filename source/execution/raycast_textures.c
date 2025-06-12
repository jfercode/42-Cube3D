/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:31:52 by penpalac          #+#    #+#             */
/*   Updated: 2025/06/12 15:49:17 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	draw_ceiling_and_floor(int wall_top, int wall_bottom,
		t_ray_cast *rc, t_game *game)
{
	int	i;

	i = 0;
	while (i < wall_top)
	{
		put_pixel_frame(game->frame, rc->ray, i,
			convert_color(game->cub3d->ceiling_rgb[0],
				game->cub3d->ceiling_rgb[1], game->cub3d->ceiling_rgb[2]));
		i++;
	}
	i = wall_bottom;
	while (i < WIN_HEIGHT)
	{
		put_pixel_frame(game->frame, rc->ray, i,
			convert_color(game->cub3d->floor_rgb[0], game->cub3d->floor_rgb[1],
				game->cub3d->floor_rgb[2]));
		i++;
	}
}

static t_tile	*get_door_texture(t_game *game)
{
	if (game->cub3d->door_frame == 1)
		return (game->door[1]);
	else if (game->cub3d->door_frame == 2)
		return (game->door[2]);
	else if (game->cub3d->door_frame == 3)
		return (game->door[3]);
	else
		return (game->door[0]);
}

static t_tile	*get_texture(t_game *game, int hit, int side, double ray_angle)
{
	if (hit == 2)
		return (get_door_texture(game));
	else
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
}

static int	get_tex_x(t_tile *texture, t_game *game, t_ray_cast *rc)
{
	int	tex_x;

	if (texture == game->north || texture == game->south)
		tex_x = (int)(rc->ray_x) % TILE_SIZE;
	else if (texture == game->east || texture == game->west)
		tex_x = (int)(rc->ray_y) % TILE_SIZE;
	else
	{
		if (rc->side == 0)
			tex_x = (int)(rc->ray_y) % TILE_SIZE;
		else
			tex_x = (int)(rc->ray_x) % TILE_SIZE;
	}
	tex_x = (tex_x * texture->x) / TILE_SIZE;
	return (tex_x);
}

void	draw(int wall_top, int wall_bottom, t_ray_cast *rc, t_game *game)
{
	t_tile	*texture;
	int		tex_x;
	int		tex_y;
	int		color;
	int		i;

	texture = get_texture(game, rc->hit, rc->side, rc->ray_angle);
	tex_x = get_tex_x(texture, game, rc);
	draw_ceiling_and_floor(wall_top, wall_bottom, rc, game);
	i = wall_top;
	while (i < wall_bottom)
	{
		tex_y = ((i - wall_top) * texture->y) / (wall_bottom - wall_top);
		color = *(int *)(texture->addr + tex_y * texture->size_line + tex_x
				* (texture->bits / 8));
		put_pixel_frame(game->frame, rc->ray, i, color);
		i++;
	}
}

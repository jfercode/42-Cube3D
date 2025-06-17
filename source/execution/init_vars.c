/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:22:16 by penpalac          #+#    #+#             */
/*   Updated: 2025/06/17 16:14:19 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	init_player_dir_part_two(t_game *game, char dir)
{
	if (dir == 'E')
	{
		game->player->dir_x = 1.0;
		game->player->dir_y = 0.0;
		game->player->plane_x = 0.0;
		game->player->plane_y = 0.66;
		game->player->dir = 0.0;
	}
	else if (dir == 'W')
	{
		game->player->dir_x = 1.0;
		game->player->dir_y = 0.0;
		game->player->plane_x = 0.0;
		game->player->plane_y = -0.66;
		game->player->dir = 0.0;
	}
}

static void	init_player_dir(t_game *game, char dir)
{
	if (dir == 'N')
	{
		game->player->dir_x = 0.0;
		game->player->dir_y = -1.0;
		game->player->plane_x = 0.66;
		game->player->plane_y = 0.0;
		game->player->dir = -M_PI / 2;
	}
	else if (dir == 'S')
	{
		game->player->dir_x = 0.0;
		game->player->dir_y = 1.0;
		game->player->plane_x = -0.66;
		game->player->plane_y = 0.0;
		game->player->dir = M_PI / 2;
	}
	init_player_dir_part_two(game, dir);
}

static void	init_player(t_game *game)
{
	game->player = ft_calloc(sizeof(t_player), 1);
	if (!game->player)
		ft_error("Calloc in init_player");
	game->player->pos_x = (game->cub3d->player_x + 0.5) * TILE_SIZE;
	game->player->pos_y = (game->cub3d->player_y + 0.5) * TILE_SIZE;
	init_player_dir(game, game->cub3d->player_dir);
	game->player->keys = ft_calloc(sizeof(t_keys), 1);
	if (!game->player->keys)
		ft_error("Calloc in init_player");
}

static void	init_textures(t_game *game)
{
	int	i;

	i = 0;
	game->north = ft_calloc(sizeof(t_tile), 1);
	if (!game->north)
		ft_error("Calloc on north");
	game->south = ft_calloc(sizeof(t_tile), 1);
	if (!game->south)
		ft_error("Calloc on south");
	game->east = ft_calloc(sizeof(t_tile), 1);
	if (!game->east)
		ft_error("Calloc on east");
	game->west = ft_calloc(sizeof(t_tile), 1);
	if (!game->west)
		ft_error("Calloc on west");
	game->frame = ft_calloc(sizeof(t_tile), 1);
	if (!game->frame)
		ft_error("Calloc on frame");
	while (i < 4 && game->cub3d->door_texture[i])
	{
		game->door[i] = ft_calloc(sizeof(t_tile), 1);
		if (!game->door[i])
			ft_error("Calloc on door");
		i++;
	}
}

void	init_game(t_game *game, t_cub3d *cub3d)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_error("Couldn't load mlx");
	game->window = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	game->cub3d = cub3d;
	game->width = ft_strlen(cub3d->map[0]);
	game->height = 0;
	while (cub3d->map[game->height])
		game->height++;
	init_textures(game);
	game->frame->x = WIN_WIDTH;
	game->frame->y = WIN_HEIGHT;
	assign_images(game);
	init_player(game);
}

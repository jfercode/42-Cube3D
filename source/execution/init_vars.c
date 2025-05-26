/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:22:16 by penpalac          #+#    #+#             */
/*   Updated: 2025/05/26 18:39:38 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void get_player_pos(t_game *game, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (ft_strchr("NSEW", map->map[i][j]) != NULL)
			{
				game->player->pos_x = j * TILE_SIZE;
				game->player->pos_y = i * TILE_SIZE;
			}
			j++;
		}
		i++;
	}
}

static void init_player(t_game *game, t_map *map)
{
	game->player = ft_calloc(sizeof(t_player), 1);
	if (!game->player)
		ft_error("Calloc in init_player");
    get_player_pos(game, map);
	game->player->dir = M_PI / 2;
	//vvv this should change depending on NSEW
	game->player->dir_x = 0;
	game->player->dir_y = 0;
	game->player->plane_x = 0;
	game->player->plane_y = 0;
}

static void	init_textures(t_game *game)
{
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
	game->frame->x = WIN_WIDTH;
	game->frame->y = WIN_HEIGHT;
}

void	init_game(t_game *game, t_map *map)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_error("Couldn't load mlx");
	game->window = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	game->map = map;
	game->height = WIN_HEIGHT;
	game->width = WIN_WIDTH;
	game->keys = ft_calloc(sizeof(t_keys), 1);
	init_textures(game);
	assign_images(game, map);
	init_player(game, map);
}


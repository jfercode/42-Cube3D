/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:41:39 by jaferna2          #+#    #+#             */
/*   Updated: 2025/06/09 18:19:36 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	ft_free_wall_textures(t_wall_textures *wall_textures)
{
	if (!wall_textures)
		return ;
	if (wall_textures->north)
		free(wall_textures->north);
	if (wall_textures->south)
		free(wall_textures->south);
	if (wall_textures->east)
		free(wall_textures->east);
	if (wall_textures->west)
		free(wall_textures->west);
	if (wall_textures)
		free(wall_textures);
	wall_textures = NULL;
}

static void	ft_free_player(t_player *player)
{
	if (!player)
		return;
	if (player->keys)
		free(player->keys);
	free(player);
}

void	ft_free_cub3d(t_cub3d *cub3d)
{
	int	i;

	if (!cub3d)
		return ;
	ft_free_wall_textures(cub3d->wall_textures);
	if (*cub3d->door_texture)
	{
		i = 0;
		while (cub3d->door_texture[i])
		{
			free(cub3d->door_texture[i]);
			i++;
		}
	}
	ft_free_matrix(cub3d->map);
	free(cub3d);
	cub3d = NULL;
}

void	ft_free_game(t_game *game)
{
	ft_free_cub3d(game->cub3d);
	ft_free_player(game->player);
}

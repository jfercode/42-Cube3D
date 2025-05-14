/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:54:01 by penpalac          #+#    #+#             */
/*   Updated: 2025/05/14 17:56:52 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	xpm_check(t_game *game)
{
	if (!game->north || !game->south || !game->east || !game->west
		|| !game->frame)
	{
		// img_destroyer(game);
		mlx_destroy_window(game->mlx, game->window);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		ft_error("Couldn't load xpm files");
	}
}

void	assign_images(t_game *game, t_map *map)
{
	game->frame->img = mlx_new_image(game->mlx, map->col, map->line);
	game->north->img = mlx_xpm_file_to_image(game->mlx, map->paths->N_path,
			&game->north->bits, &game->north->size_line);
	game->south->img = mlx_xpm_file_to_image(game->mlx, map->paths->S_path,
			&game->south->bits, &game->south->size_line);
	game->west->img = mlx_xpm_file_to_image(game->mlx, map->paths->W_path,
			&game->west->bits, &game->west->size_line);
	game->east->img = mlx_xpm_file_to_image(game->mlx, map->paths->E_path,
			&game->east->bits, &game->east->size_line);
	xpm_check(game);
	game->frame->addr = mlx_get_data_addr(game->frame->img, &game->frame->bits,
			&game->frame->size_line, &game->frame->endian);
	game->north->addr = mlx_get_data_addr(game->north->img, &game->north->bits,
			&game->north->size_line, &game->north->endian);
	game->south->addr = mlx_get_data_addr(game->south->img, &game->south->bits,
			&game->south->size_line, &game->south->endian);
	game->east->addr = mlx_get_data_addr(game->east->img, &game->east->bits,
			&game->east->size_line, &game->east->endian);
	game->west->addr = mlx_get_data_addr(game->west->img, &game->west->bits,
			&game->west->size_line, &game->west->endian);
}

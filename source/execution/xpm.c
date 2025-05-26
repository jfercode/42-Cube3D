/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:54:01 by penpalac          #+#    #+#             */
/*   Updated: 2025/05/26 18:39:40 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void free_imgs(t_game *game)
{
	mlx_destroy_image(game->mlx, game->frame->img);
	mlx_destroy_image(game->mlx, game->north->img);
	mlx_destroy_image(game->mlx, game->south->img);
	mlx_destroy_image(game->mlx, game->west->img);
	mlx_destroy_image(game->mlx, game->east->img);
}

static void	xpm_check(t_game *game)
{
	if (!game->north->img || !game->south->img || !game->east->img \
		|| !game->west->img || !game->frame->img)
	{
		free_imgs(game);
		mlx_destroy_window(game->mlx, game->window);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		ft_error("Couldn't load xpm files");
	}
}

void	assign_images(t_game *game, t_map *map)
{
	game->frame->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->north->img = mlx_xpm_file_to_image(game->mlx, map->paths->N_path,
			&game->north->x, &game->north->y);
	game->south->img = mlx_xpm_file_to_image(game->mlx, map->paths->S_path,
			&game->south->x, &game->south->y);
	game->west->img = mlx_xpm_file_to_image(game->mlx, map->paths->W_path,
			&game->west->x, &game->west->y);
	game->east->img = mlx_xpm_file_to_image(game->mlx, map->paths->E_path,
			&game->east->x, &game->east->y);
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

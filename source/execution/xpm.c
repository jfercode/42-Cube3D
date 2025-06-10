/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:54:01 by penpalac          #+#    #+#             */
/*   Updated: 2025/06/10 18:34:23 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	xpm_check(t_game *game)
{
	if (!game->north->img || !game->south->img || !game->east->img
		|| !game->west->img || !game->frame->img)
	{
		ft_error("Couldn't load xpm files");
		close_game(game);
	}
}

static void	assign_images_bonus(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->door[i]->img = mlx_xpm_file_to_image(game->mlx,
				game->cub3d->door_texture[i], &game->door[i]->x,
				&game->door[i]->y);
		if (!game->door[i]->img)
		{
			ft_error("Couldn't load xpm files");
			close_game(game);
		}
		i++;
	}
	i = 0;
	while (i < 4)
	{
		game->door[i]->addr = mlx_get_data_addr(game->door[i]->img,
				&game->door[i]->bits, &game->door[i]->size_line,
				&game->door[i]->endian);
		i++;
	}
}

void	assign_images(t_game *game)
{
	game->frame->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->north->img = mlx_xpm_file_to_image(game->mlx,
			game->cub3d->wall_textures->north, &game->north->x,
			&game->north->y);
	game->south->img = mlx_xpm_file_to_image(game->mlx,
			game->cub3d->wall_textures->south, &game->south->x,
			&game->south->y);
	game->west->img = mlx_xpm_file_to_image(game->mlx,
			game->cub3d->wall_textures->west, &game->west->x, &game->west->y);
	game->east->img = mlx_xpm_file_to_image(game->mlx,
			game->cub3d->wall_textures->east, &game->east->x, &game->east->y);
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
	if (IS_BONUS)
		assign_images_bonus(game);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:11:49 by penpalac          #+#    #+#             */
/*   Updated: 2025/06/17 16:16:19 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	free_images(t_game *game)
{
	int	i;

	i = 0;
	mlx_destroy_image(game->mlx, game->frame->img);
	mlx_destroy_image(game->mlx, game->north->img);
	mlx_destroy_image(game->mlx, game->south->img);
	mlx_destroy_image(game->mlx, game->west->img);
	mlx_destroy_image(game->mlx, game->east->img);
	free(game->frame);
	free(game->north);
	free(game->south);
	free(game->east);
	free(game->west);
	while (i < 4 && game->cub3d->door_texture[i])
	{
		mlx_destroy_image(game->mlx, game->door[i]->img);
		free(game->door[i]);
		i++;
	}
}

int	close_game(t_game *game)
{
	free_images(game);
	mlx_destroy_window(game->mlx, game->window);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	ft_free_game(game);
	exit(EXIT_SUCCESS);
	return (0);
}

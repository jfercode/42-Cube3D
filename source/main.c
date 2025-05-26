/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:00:07 by penpalac          #+#    #+#             */
/*   Updated: 2025/05/26 18:48:49 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	main(int ac, char **av)
{
	t_cub3d	*basic_str;
	t_game	*game;

	if (ac > 2)
		ft_error("Invalid number of arguments");
	basic_str = malloc(sizeof(t_cub3d));
	if (!basic_str->wall_textures)
		basic_str->wall_textures = malloc(sizeof(t_wall_textures));
	if (!basic_str || !basic_str->wall_textures)
		return (1);
	if (ac < 2)
		return (1);
	else
	{
		if (file_validation(av[1], basic_str) == SUCCESS)
			ft_printf(STDOUT_FILENO, "OK\n");
	}
	game = ft_calloc(sizeof(t_game), sizeof(t_game));
	if (!game)
		return (free(game), 1);
	init_game(game, map);
	start_game(game, map);
	return (0);
}

void	start_game(t_game *game, t_map *map)
{
	raycast(game);
	mlx_hook(game->window, ClientMessage, LeaveWindowMask, close_game, game);
	mlx_key_hook(game->window, key_input, game);
	mlx_loop(game->mlx);
}

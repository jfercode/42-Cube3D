/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:00:07 by penpalac          #+#    #+#             */
/*   Updated: 2025/06/09 18:15:14 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	ft_init_cub3d(t_cub3d **cub3d)
{
	*cub3d = malloc(sizeof(t_cub3d));
	if (!*cub3d)
		return (ft_printf(STDERR_FILENO, "Error:\n failed malloc\n"),
			EXIT_FAILURE);
	(*cub3d)->wall_textures = malloc(sizeof(t_wall_textures));
	if (!(*cub3d)->wall_textures)
		return (ft_printf(STDERR_FILENO, "Error:\n failed malloc\n"),
			EXIT_FAILURE);
	(*cub3d)->wall_textures->north = NULL;
	(*cub3d)->wall_textures->south = NULL;
	(*cub3d)->wall_textures->east = NULL;
	(*cub3d)->wall_textures->west = NULL;
	(*cub3d)->map_started = false;
	(*cub3d)->floor_assigned = false;
	(*cub3d)->ceiling_assigned = false;
	(*cub3d)->door_texture = NULL;
	(*cub3d)->map = NULL;
	return (EXIT_SUCCESS);
}

static int	game_loop(t_game *game)
{
	update_player(game);
	raycast(game);
	if (IS_BONUS == 1)
	{
		mlx_mouse_hide(game->mlx, game->window);
		mlx_mouse_move(game->mlx, game->window, game->width / 2, game->height
			/ 2);
	}
	return (SUCCESS);
}

void	start_game(t_game *game)
{
	raycast(game);
	mlx_hook(game->window, ClientMessage, LeaveWindowMask, close_game, game);
	mlx_hook(game->window, 2, 1L << 0, key_press, game);
	mlx_hook(game->window, 3, 1L << 1, key_release, game);
	if (IS_BONUS == 1)
	{
		mlx_mouse_hide(game->mlx, game->window);
		mlx_hook(game->window, 6, 1L << 6, mouse_move, game);
	}
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
}

int	main(int ac, char **av)
{
	t_cub3d	*basic_str;
	t_game	*game;

	basic_str = NULL;
	if (ft_init_cub3d(&basic_str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ac != 2)
		return (EXIT_FAILURE);
	else
	{
		if (ft_file_validation(av[1], basic_str) == SUCCESS)
			ft_print_cub3d(basic_str);
		else
			return (ft_free_cub3d(basic_str), EXIT_FAILURE);
	}
	game = ft_calloc(sizeof(t_game), 1);
	if (!game)
		return (free(game), 1);
	init_game(game, basic_str);
	start_game(game);
	return (EXIT_SUCCESS);
}

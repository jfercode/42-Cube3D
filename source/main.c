/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:00:07 by penpalac          #+#    #+#             */
/*   Updated: 2025/05/12 19:36:27 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_error(char *str)
{
	printf("Error\n%s", str);
	// perror(str);
	exit(EXIT_FAILURE);
}

t_map	*parse_map(char **av)
{
	return (NULL);
}

// might need a struct with routes and colors and the map matrix to send back
int	main(int ac, char **av)
{
	t_game	*game;
	t_map	*map;

	if (ac != 2)
		ft_error("Invalid number of arguments");
	map = parse_map(av[1]);
	game = ft_calloc(sizeof(t_game), 1);
	if (!game)
		return (free(game), 1);
	prepare_map(game, map);
	return (0);
}

void	prepare_map(t_game *game, t_map *map)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_error("Couldn't load mlx");
	game->window = mlx_new_window(game->mlx, map->line * TILE_SIZE, map->col
			* TILE_SIZE, "cub3D");
	assign_images(game, map);
	// destroy map
	start_game(game);
}

void	assign_images(t_game *game, t_map *map)
{
	game->north = mlx_xpm_file_to_image(game->mlx, map->paths->N_text, TILE_SIZE,
			TILE_SIZE);
	game->south = mlx_xpm_file_to_image(game->mlx, map->paths->S_text, TILE_SIZE,
			TILE_SIZE);
	game->west = mlx_xpm_file_to_image(game->mlx, map->paths->W_text, TILE_SIZE,
			TILE_SIZE);
	game->east = mlx_xpm_file_to_image(game->mlx, map->paths->E_text, TILE_SIZE,
			TILE_SIZE);
	if (!game->north || !game->south || !game->west || !game->east)
	{
		//destroy all
		free(game);
		ft_error("Couldn't load textures");
	}
	//No idea on how to assign colors
}

void	start_game(t_game *game)
{
	//draw map and I guess raycasting
	mlx_key_hook(game->window, key_input, game);
	mlx_hook(game->window, ClientMessage, LeaveWindowMask, close_game, game);
	mlx_loop(game->mlx);
}

void	key_input(int keycode, t_game *game)
{
	if (keycode == K_ESC)
		close_game(game);
	else if (keycode == K_W)
		move_up(game);
	else if (keycode == K_A)
		move_left(game);
	else if (keycode == K_S)
		move_down(game);
	else if (keycode == K_D)
		move_right(game);
	else if (keycode == K_AR_R)
		move_down(game);
	else if (keycode == K_AR_L)
		move_right(game);
	return (0);
}

void	close_game(t_game *game)
{
	mlx_destroy_image(game->mlx, game->north);
	mlx_destroy_image(game->mlx, game->south);
	mlx_destroy_image(game->mlx, game->west);
	mlx_destroy_image(game->mlx, game->east);
	mlx_destroy_window(game->mlx, game->window);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
	exit(EXIT_SUCCESS);
}

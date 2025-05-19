/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:00:07 by penpalac          #+#    #+#             */
/*   Updated: 2025/05/19 13:58:18 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_error(char *str)
{
	ft_putendl_fd("Error\n", 2);
	ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}

// temporary function, replaces parsing
t_map	*init_map(void)
{
	t_map	*map;

	map = ft_calloc(sizeof(t_map), 1);
	if (!map)
		ft_error("Calloc on map");
	map->map = ft_split("1111111,1000001,1000001,1000001,1000001,1000001,1000001,1000001,1000001,1000001,1000001,1000001,1000001,1000001,100N001,1111111",
			',');
	map->col = 21;
	map->line = 8;
	map->paths = ft_calloc(sizeof(t_paths), 1);
	if (!map->paths)
		ft_error("Calloc on paths");
	map->paths->N_path = "textures/0_floor.xpm";
	map->paths->S_path = "textures/1_wall.xpm";
	map->paths->E_path = "textures/P_player.xpm";
	map->paths->W_path = "textures/C_item.xpm";
	map->colors = ft_calloc(sizeof(t_colors), 1);
	if (!map->colors)
		ft_error("Calloc on colors");
	map->colors->ceiling = "200,200,200";
	map->colors->floor = "200,200,200";
	return (map);
}

// might need a struct with routes and colors and the map matrix to send back
int	main(int ac, char **av)
{
	t_game	*game;
	t_map	*map;

	map = init_map();
	if (ac > 2)
		ft_error("Invalid number of arguments");
	// map = parse_map(av[1]);
	(void)av;
	game = ft_calloc(sizeof(t_game), sizeof(t_game));
	if (!game)
		return (free(game), 1);
	init_game(game, map);
	start_game(game, map);
	return (0);
}

// init t_game variables
void	init_game(t_game *game, t_map *map)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_error("Couldn't load mlx");
	game->window = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
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
	game->map = map;
	game->frame->x = WIN_WIDTH;
	game->frame->y = WIN_HEIGHT;
	game->height = WIN_HEIGHT;
	game->width = WIN_WIDTH;
	assign_images(game, map);
}

// function that calls everything in the loop
void	start_game(t_game *game, t_map *map)
{
	game->player.x = 2.5 * TILE_SIZE;
	game->player.y = 2.5 * TILE_SIZE;
	game->player.dir = M_PI / 2;
	game->dir_x = 0;
	game->dir_y = 1;
	game->plane_x = 0.66;
	game->plane_y = 0;
	// mlx_key_hook(game->window, key_input, game);
	mlx_hook(game->window, ClientMessage, LeaveWindowMask, close_game, game);
	mlx_loop_hook(game->mlx, &raycast, game);
	mlx_loop(game->mlx);
}

// close game cleanly
int	close_game(t_game *game)
{
	mlx_destroy_image(game->mlx, game->frame->img);
	mlx_destroy_image(game->mlx, game->north->img);
	mlx_destroy_image(game->mlx, game->south->img);
	mlx_destroy_image(game->mlx, game->west->img);
	mlx_destroy_image(game->mlx, game->east->img);
	mlx_destroy_window(game->mlx, game->window);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
	exit(EXIT_SUCCESS);
	return (0);
}

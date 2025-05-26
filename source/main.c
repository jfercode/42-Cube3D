/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:00:07 by penpalac          #+#    #+#             */
/*   Updated: 2025/05/26 18:37:12 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// temporary function, replaces parsing
t_map	*init_map(void)
{
	t_map	*map;

	map = ft_calloc(sizeof(t_map), 1);
	if (!map)
		ft_error("Calloc on map");
	map->map = ft_split("1111111,1000001,10N0001,1000001,1000001,1000001,1000001,1000001,1001001,1000001,1000001,1111111",
			',');
    map->width = ft_strlen(map->map[0]); // Width is the number of columns in the first row
    map->height = 0;
    while (map->map[map->height] != NULL) // Height is the number of rows
        map->height++;

    printf("width: %d, height: %d\n", map->width, map->height);
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

void	ft_error(char *str)
{
	ft_putendl_fd("Error\n", 2);
	ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}

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

void	start_game(t_game *game, t_map *map)
{
	raycast(game);
	mlx_hook(game->window, ClientMessage, LeaveWindowMask, close_game, game);
	// mlx_key_hook(game->window, key_press, &game);             // Solo para ESC
    // mlx_hook(game->window, 2, 1L<<0, key_press, &game);       // KeyPress
    // mlx_hook(game->window, 3, 1L<<1, key_release, &game);     // KeyRelease
    // mlx_loop_hook(game->mlx, loop_hook, &game);            // Se llama cada frame
	mlx_key_hook(game->window, key_input, game);
	mlx_loop(game->mlx);
}

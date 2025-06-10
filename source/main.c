/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:00:07 by penpalac          #+#    #+#             */
/*   Updated: 2025/06/10 17:30:09 by penpalac         ###   ########.fr       */
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
	(*cub3d)->door_texture[0] = NULL;
	(*cub3d)->map = NULL;
	return (EXIT_SUCCESS);
}

int	update_loop(t_game *game)
{
	long long	current_time;

	if (game->door_anim.animating)
	{
		printf("IF\n");
		current_time = get_time();
		// Change frame every 1000ms (1 second)
		if (current_time - game->door_anim.start_time >= 1000)
		{
			printf("IF2\n");
			game->door_anim.frame++;
			game->door_anim.start_time = current_time;
			if (game->door_anim.frame >= 4)
			{
				printf("animation complete?\n");
				// Animation complete
				game->door_anim.animating = 0;
				game->cub3d->map[game->door_anim.target_y][game->door_anim.target_x] = '0';
				game->flag = 0;
			}
			else
			{
				game->flag = game->door_anim.frame; // Update texture
			}
		}
	}
	printf("raycast time\n");
	raycast(game);
	mlx_put_image_to_window(game->mlx, game->window, game->frame, 0, 0);
		// Assuming game->image is your rendered image
	return (0);
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
		mlx_hook(game->window, 2, 1L << 0, update_loop, game);
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

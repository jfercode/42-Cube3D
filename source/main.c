/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:00:07 by penpalac          #+#    #+#             */
/*   Updated: 2025/05/14 18:20:28 by penpalac         ###   ########.fr       */
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
	map->map = ft_split("1111111,1000001,1000001,1000001,1000001,1000001,100N001,1111111",
			',');
	map->col = 4;
	map->line = 12;
	map->paths = ft_calloc(sizeof(t_paths), 1);
	map->paths->N_path = "textures/0_floor.xpm";
	map->paths->S_path = "textures/1_wall.xpm";
	map->paths->E_path = "textures/P_player.xpm";
	map->paths->W_path = "textures/C_item.xpm";
	map->colors = ft_calloc(sizeof(t_colors), 1);
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
	return (0);
}

// init t_game variables
void	init_game(t_game *game, t_map *map)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_error("Couldn't load mlx");
	game->window = mlx_new_window(game->mlx, map->line * TILE_SIZE, map->col
			* TILE_SIZE, "cub3D");
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
	assign_images(game, map);
	start_game(game, map);
}

// function that calls everything in the loop
void	start_game(t_game *game, t_map *map)
{
	game->player.x = 2.5 * TILE_SIZE;
	game->player.y = 2.5 * TILE_SIZE;
	game->player.dir = M_PI / 2;
	// destroy map
	// mlx_key_hook(game->window, key_input, game);
	mlx_loop_hook(game->mlx, &raycast, game);
	mlx_hook(game->window, ClientMessage, LeaveWindowMask, close_game, game);
	mlx_loop(game->mlx);
}

void	put_pixel_frame(t_tile *frame, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= frame->x || y >= frame->y)
		return;
	dst = frame->addr + (y * frame->size_line + x * (frame->bits / 8));
	*(unsigned int *)dst = color;
}

void	draw(int wall_top, int wall_bottom, int ray, t_game *game, double ray_x,
		double ray_y, double ray_angle)
{
	t_tile	*texture;
	int		tex_x;
	int		tex_y;
	int		color;
	int		i;

	texture = get_texture(game, ray_x, ray_y, ray_angle);
	if (texture == game->north || texture == game->south)
		tex_x = (int)(ray_x) % TILE_SIZE;
	else
		tex_x = (int)(ray_y) % TILE_SIZE;
	tex_x = (tex_x * texture->x) / TILE_SIZE;
	i = 0;
	while (i < wall_top)
	{
		put_pixel_frame(texture, ray, i, 0x69B00B);
		i++;
	}
	i = wall_top;
	while (i < wall_bottom)
	{
		put_pixel_frame(texture, ray, i, 0x222222);
		i++;
	}
	i = 0;
	while (i < wall_bottom)
	{
		put_pixel_frame(texture, ray, i, 0xB00B69);
		i++;
	}
}

int	raycast(t_game *game)
{
	t_player	*player;
	t_map		*map;
	double		wall_height;
	double		angle_step;
	double		ray_angle;
	double		corrected;
	double		distance;
	int			wall_bottom;
	int			wall_top;
	int			ray;
	int			hit;

	map = game->map;
	player = &game->player;
	angle_step = FOV / NUM_RAYS;
	ray_angle = player->dir - (FOV / 2);
	ray = 0;
	while (ray < NUM_RAYS)
	{
		distance = 0;
		double ray_x, ray_y;
		hit = 0;
		int map_x, map_y;
		while (distance < MAX_DEPTH && !hit)
		{
			ray_x = player->x + cos(ray_angle) * distance;
			ray_y = player->y + sin(ray_angle) * distance;
			map_x = (int)(ray_x / TILE_SIZE);
			map_y = (int)(ray_y / TILE_SIZE);
			if (map_y < 0 || map_y >= map->col || map_x < 0
				|| map_x >= map->line)
				break ;
			if (map->map[map_y][map_x] == '1')
				hit = 1;
			distance += 1;
		}
		corrected = distance * cos(ray_angle - player->dir);
		if (corrected < 0.1)
			corrected = 0.1;
		wall_height = (TILE_SIZE * game->height) / corrected;
		if (wall_height > game->height)
			wall_height = game->height;
		wall_top = (game->height / 2) - (wall_height / 2);
		wall_bottom = wall_top + wall_height;
		// draw
		draw(wall_top, wall_bottom, ray, game, ray_x, ray_y, ray_angle);
		ray_angle += angle_step;
		ray++;
	}
	//mlx_put_image_to_window(game->mlx, game->window, game->frame->img, 0, 0);
	return (0);
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

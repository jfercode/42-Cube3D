/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_physics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:31:05 by jaferna2          #+#    #+#             */
/*   Updated: 2025/06/09 17:24:14 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	movement(t_game *game, double x, double y)
{
	double	new_x;
	double	new_y;

	new_x = game->player->pos_x + x;
	new_y = game->player->pos_y + y;
	if (game->cub3d->map[(int)(game->player->pos_y / TILE_SIZE)][(int)((new_x
				+ OFFSET) / TILE_SIZE)] != '1'
		&& game->cub3d->map[(int)(game->player->pos_y / TILE_SIZE)][(int)((new_x
				- OFFSET) / TILE_SIZE)] != '1'
		&& game->cub3d->map[(int)(game->player->pos_y / TILE_SIZE)][(int)((new_x
				+ OFFSET) / TILE_SIZE)] != 'D'
		&& game->cub3d->map[(int)(game->player->pos_y / TILE_SIZE)][(int)((new_x
				- OFFSET) / TILE_SIZE)] != 'D')
	{
		game->player->pos_x = new_x;
	}
	if (game->cub3d->map[(int)((new_y + OFFSET)
			/ TILE_SIZE)][(int)(game->player->pos_x / TILE_SIZE)] != '1'
		&& game->cub3d->map[(int)((new_y - OFFSET)
			/ TILE_SIZE)][(int)(game->player->pos_x / TILE_SIZE)] != '1'
		&& game->cub3d->map[(int)((new_y + OFFSET)
			/ TILE_SIZE)][(int)(game->player->pos_x / TILE_SIZE)] != 'D'
		&& game->cub3d->map[(int)((new_y - OFFSET)
			/ TILE_SIZE)][(int)(game->player->pos_x / TILE_SIZE)] != 'D')
	{
		game->player->pos_y = new_y;
	}
}

void	rotate(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player->dir_x;
	old_plane_x = game->player->plane_x;
	game->player->dir_x = game->player->dir_x * cos(angle) - game->player->dir_y
		* sin(angle);
	game->player->dir_y = old_dir_x * sin(angle) + game->player->dir_y
		* cos(angle);
	game->player->plane_x = game->player->plane_x * cos(angle)
		- game->player->plane_y * sin(angle);
	game->player->plane_y = old_plane_x * sin(angle) + game->player->plane_y
		* cos(angle);
	game->player->dir = atan2(game->player->dir_y, game->player->dir_x);
}

void	update_player(t_game *game)
{
	if (game->player->keys->w)
		movement(game, game->player->dir_x * SPEED, game->player->dir_y
			* SPEED);
	else if (game->player->keys->d)
		movement(game, -game->player->dir_y * SPEED, game->player->dir_x
			* SPEED);
	else if (game->player->keys->s)
		movement(game, -game->player->dir_x * SPEED, -game->player->dir_y
			* SPEED);
	else if (game->player->keys->a)
		movement(game, game->player->dir_y * SPEED, -game->player->dir_x
			* SPEED);
	else if (game->player->keys->left)
		rotate(game, -ROT_SPEED);
	else if (game->player->keys->right)
		rotate(game, ROT_SPEED);
}

time_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(time_t time)
{
	time_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(1000);
	return (0);
}

void	open_door(t_game *game)
{
	int		target_x;
	int		target_y;
	double	x;
	double	y;
	int		i;

	i = 0;
	x = game->player->pos_x + game->player->dir_x * TILE_SIZE * 1.5;
	y = game->player->pos_y + game->player->dir_y * TILE_SIZE * 1.5;
	target_x = (int)(x / TILE_SIZE);
	target_y = (int)(y / TILE_SIZE);
	if (target_x < 0 || target_y < 0 || target_y >= game->height
		|| target_x >= game->width)
		return ;
	if (game->cub3d->map[target_y][target_x] == 'D')
	{
		while (game->door[i])
		{
			mlx_put_image_to_window(game->mlx, game->window,
					game->door[i], game->door[i]->x, game->door[i]->y);
			ft_usleep(500);
		}
		game->cub3d->map[target_y][target_x] = '0';
	}
}

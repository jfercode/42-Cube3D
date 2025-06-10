/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mapping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:06:08 by penpalac          #+#    #+#             */
/*   Updated: 2025/06/10 17:27:10 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == K_ESC)
		close_game(game);
	else if (keycode == K_W)
		game->player->keys->w = 1;
	else if (keycode == K_D)
		game->player->keys->d = 1;
	else if (keycode == K_S)
		game->player->keys->s = 1;
	else if (keycode == K_A)
		game->player->keys->a = 1;
	else if (keycode == K_AR_L)
		game->player->keys->left = 1;
	else if (keycode == K_AR_R)
		game->player->keys->right = 1;
	else if (IS_BONUS && keycode == K_E)
			open_door(game);
	else
		return (FAIL);
	return (SUCCESS);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == K_ESC)
		close_game(game);
	else if (keycode == K_W)
		game->player->keys->w = 0;
	else if (keycode == K_D)
		game->player->keys->d = 0;
	else if (keycode == K_S)
		game->player->keys->s = 0;
	else if (keycode == K_A)
		game->player->keys->a = 0;
	else if (keycode == K_AR_L)
		game->player->keys->left = 0;
	else if (keycode == K_AR_R)
		game->player->keys->right = 0;
	else
		return (FAIL);
	return (SUCCESS);
}

int	mouse_move(int x, int y, t_game *game)
{
	int			delta_x;
	double		angle;
	const int	center_x = game->width / 2;

	(void)y;
	if (!game || !game->player)
		return (0);
	delta_x = x - center_x;
	if (delta_x > 0)
		delta_x = 1;
	else if (delta_x < 0)
		delta_x = -1;
	angle = delta_x * MOUSE_SENSITIVITY;
	if (angle != 0)
		rotate(game, angle);
	mlx_mouse_move(game->mlx, game->window, center_x, game->height / 2);
	return (0);
}

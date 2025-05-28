/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mapping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:06:08 by penpalac          #+#    #+#             */
/*   Updated: 2025/05/28 16:45:48 by jaferna2         ###   ########.fr       */
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

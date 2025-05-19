/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mapping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:06:08 by penpalac          #+#    #+#             */
/*   Updated: 2025/05/19 19:10:18 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	key_input(int keycode, t_game *game)
{
	if (keycode == K_ESC)
		close_game(game);
	else if (keycode == K_W)
		printf("W");
	else if (keycode == K_A)
		printf("A");
	else if (keycode == K_S)
		printf("S");
	else if (keycode == K_D)
		printf("D");
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:00:07 by penpalac          #+#    #+#             */
/*   Updated: 2025/05/13 17:01:04 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	main(int ac, char **av)
{
	t_cub3d	*basic_str;

	basic_str = malloc(sizeof(t_cub3d));
	if (!basic_str->wall_textures)
		basic_str->wall_textures = malloc(sizeof(t_wall_textures));
	if (!basic_str)
		return (1);
	if (ac < 2)
		return (1);
	else
	{
		if (file_validation(av[1], basic_str))
			printf("ok\n");
	}
	return (0);
}

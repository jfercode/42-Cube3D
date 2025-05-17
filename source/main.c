/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:00:07 by penpalac          #+#    #+#             */
/*   Updated: 2025/05/17 18:28:23 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	main(int ac, char **av)
{
	t_cub3d	*basic_str;

	basic_str = malloc(sizeof(t_cub3d));
	if (!basic_str->wall_textures)
		basic_str->wall_textures = malloc(sizeof(t_wall_textures));
	if (!basic_str || !basic_str->wall_textures)
		return (1);
	if (ac < 2)
		return (1);
	else
	{
		if (file_validation(av[1], basic_str) == SUCCESS)
			ft_printf(STDOUT_FILENO, "OK\n");
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:13:36 by jaferna2          #+#    #+#             */
/*   Updated: 2025/05/12 19:42:37 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

#define FAIL 0
#define SUCCESS 1

/* Check the map extension */
static int	ft_check_map_extensions(char *map_file_name)
{
	char	*extension;
	char	*file_extension;

	extension = ".cub";
	file_extension = ft_strrchr(map_file_name, '.');
	if (!file_extension)
		return (perror("Error:\n Map file has no extension\n"), FAIL);
	else if (ft_strncmp(file_extension, extension, 4))
		return (perror("Error:\n Map file has wrong extension\n"), FAIL);
	return (SUCCESS);
}

/*
	1. Extension .cub DONE
	2. read file until
		2.1 Detect Texture NO, SO, WE, EA
		2.2 Detect Color F, C
		2.3 Detect Wall or map
*/
int	file_validation(char *map_file, t_cub3d *cub3d)
{
	char	*line;

	if (!ft_check_map_extensions(map_file))
		return (FAIL);	
	return (SUCCESS);
}

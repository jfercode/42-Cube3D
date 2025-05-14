/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:13:36 by jaferna2          #+#    #+#             */
/*   Updated: 2025/05/13 17:00:05 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/* Check the map extension */
int	ft_check_map_extensions(char *map_file_name, char *extension)
{
	char	*file_extension;

	file_extension = ft_strrchr(map_file_name, '.');
	if (!file_extension)
		return (ft_printf(STDERR_FILENO, "Error:\n No extension: %s\n",
				map_file_name), FAIL);
	else if (ft_strncmp(file_extension, extension, ft_strlen(extension)))
		return (ft_printf(STDERR_FILENO, "Error:\n Wrong extension: %s\n",
				map_file_name), FAIL);
	return (SUCCESS);
}

static int	ft_line_analisis(char *line, t_cub3d *cub3d)
{
	int	i;

	i = 0;
	if (!line)
		return (FAIL);
	while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
		i++;
	if (ft_strncmp("NO", line, 2))
		return (ft_validate_texture_line(line, i + 2, 'N', cub3d));
	else if (ft_strncmp("SO", line, 2))
		return (ft_validate_texture_line(line, i + 2, 'S', cub3d));
	else if (ft_strncmp("WE", line, 2))
		return (ft_validate_texture_line(line, i + 2, 'W', cub3d));
	else if (ft_strncmp("EA", line, 2))
		return (ft_validate_texture_line(line, i + 2, 'E', cub3d));
	else if (ft_strncmp("C", line, 1))
		return (ft_validate_color_line(line, i + 1, 'C', cub3d));
	return (SUCCESS);
}

/*
	1. Extension .cub DONE
	2. read file until
		2.1 Detect Texture NO, SO, WE, EA
		2.2 Detect Color F, C
		2.3 Detect Wall or map
	pre 2 -> Analizar la linea
*/
int	file_validation(char *map_file, t_cub3d *cub3d)
{
	char	*line;
	int		fd;

	if (!ft_check_map_extensions(map_file, ".cub"))
		return (FAIL);
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (ft_printf(STDERR_FILENO, "Error\nDoesn't exist file: %s\n",
				map_file), FAIL);
	line = ft_get_next_line(fd);
	while (line != NULL)
	{
		ft_printf(STDOUT_FILENO, line);
		if (ft_line_analisis(line, cub3d) == FAIL)
			return (FAIL);
		if (line)
			free(line);
		line = NULL;
		line = ft_get_next_line(fd);
	}
	close(fd);
	return (SUCCESS);
}

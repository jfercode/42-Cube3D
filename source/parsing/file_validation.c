/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:13:36 by jaferna2          #+#    #+#             */
/*   Updated: 2025/05/15 12:36:41 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

char	*ft_strip_newline(char *str)
{
	int		len;
	char	*cleaned;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		len--;
	cleaned = ft_substr(str, 0, len);
	return (cleaned);
}

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

/*	*/
static int	ft_line_analisis(char *line, t_cub3d *cub3d)
{
	int	i;

	i = 0;
	if (!line)
		return (FAIL);
	while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
		i++;
	if (ft_strncmp("NO", &line[i], 2) == 0)
		return (ft_validate_texture_line(line, i + 2, 'N', cub3d));
	else if (ft_strncmp("SO", &line[i], 2) == 0)
		return (ft_validate_texture_line(line, i + 2, 'S', cub3d));
	else if (ft_strncmp("WE", &line[i], 2) == 0)
		return (ft_validate_texture_line(line, i + 2, 'W', cub3d));
	else if (ft_strncmp("EA", &line[i], 2) == 0)
		return (ft_validate_texture_line(line, i + 2, 'E', cub3d));
	else if (ft_strncmp("C", &line[i], 1) == 0)
		return (ft_validate_color_line(line, i + 1, 'C', cub3d));
	else if (ft_strncmp("F", &line[i], 1) == 0)
		return (ft_validate_color_line(line, i + 1, 'F', cub3d));
	return (SUCCESS);
}

static	int	ft_check_for_all_variables(t_cub3d *cub3d)
{
	if (!cub3d->wall_textures->north)
		return (ft_printf(STDERR_FILENO, "Error:\nMissing north texture\n"), FAIL);
	else if (!cub3d->wall_textures->south)
		return (ft_printf(STDERR_FILENO, "Error:\nMissing south texture\n"), FAIL);
	else if (!cub3d->wall_textures->west)
		return (ft_printf(STDERR_FILENO, "Error:\nMissing west texture\n"), FAIL);
	else if (!cub3d->wall_textures->east)
		return (ft_printf(STDERR_FILENO, "Error:\nMissing east texture\n"), FAIL);
	else if (cub3d->ceiling_assigned == false)
		return (ft_printf(STDERR_FILENO, "Error:\nMissing ceiling color\n"), FAIL);
	else if (cub3d->floor_assigned == false)
		return (ft_printf(STDERR_FILENO, "Error:\nMissing floor color\n"), FAIL);
	// TO DO CHECK MAP
	return (SUCCESS);
}

/*
	1. Extension .cub DONE
	2. read file until
		2.1 Texture NO, SO, WE, EA -> DONE 
		2.2 Color F, C
		2.3 Map
	3. Check all variables
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
		if (ft_line_analisis(line, cub3d) == FAIL)
			return (FAIL, close(fd));
		if (line)
			free(line);
		line = NULL;
		line = ft_get_next_line(fd);
	}
	close(fd);
	if (ft_check_for_all_variables(cub3d) == false)
		return (FAIL);
	return (SUCCESS);
}

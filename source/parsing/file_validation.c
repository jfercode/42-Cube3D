/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:13:36 by jaferna2          #+#    #+#             */
/*   Updated: 2025/05/26 16:26:47 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	ft_parse_identifier(char *line, int i, t_cub3d *cub3d)
{
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
	return (FAIL);
}

static int	ft_check_for_variables(t_cub3d *cub3d)
{
	if (!cub3d->wall_textures->north)
		return (ft_printf(STDERR_FILENO, "Error:\nMissing north texture\n"),
			FAIL);
	else if (!cub3d->wall_textures->south)
		return (ft_printf(STDERR_FILENO, "Error:\nMissing south texture\n"),
			FAIL);
	else if (!cub3d->wall_textures->west)
		return (ft_printf(STDERR_FILENO, "Error:\nMissing west texture\n"),
			FAIL);
	else if (!cub3d->wall_textures->east)
		return (ft_printf(STDERR_FILENO, "Error:\nMissing east texture\n"),
			FAIL);
	else if (cub3d->ceiling_assigned == false)
		return (ft_printf(STDERR_FILENO, "Error:\nMissing ceiling color\n"),
			FAIL);
	else if (cub3d->floor_assigned == false)
		return (ft_printf(STDERR_FILENO, "Error:\nMissing floor color\n"),
			FAIL);
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
	if (line[i] == '\0')
		return (SUCCESS);
	if (ft_strchr("1", line[i]))
	{
		if (ft_check_for_variables(cub3d) == SUCCESS)
			cub3d->map_started = true;
		else
			return (ft_printf(STDERR_FILENO,
					"Error:\nIncorrect map in file place\n"), FAIL);
		return (SUCCESS);
	}
	if (cub3d->map_started)
		return (ft_printf(STDERR_FILENO,
				"Error:\nUnexepected element inside the map\n"), FAIL);
	return (ft_parse_identifier(line, i, cub3d));
}

static int	ft_check_all(t_cub3d *cub3d)
{
	if (!cub3d->wall_textures->north)
		return (ft_printf(STDERR_FILENO, "Error:\nMissing north texture\n"),
			FAIL);
	else if (!cub3d->wall_textures->south)
		return (ft_printf(STDERR_FILENO, "Error:\nMissing south texture\n"),
			FAIL);
	else if (!cub3d->wall_textures->west)
		return (ft_printf(STDERR_FILENO, "Error:\nMissing west texture\n"),
			FAIL);
	else if (!cub3d->wall_textures->east)
		return (ft_printf(STDERR_FILENO, "Error:\nMissing east texture\n"),
			FAIL);
	else if (cub3d->ceiling_assigned == false)
		return (ft_printf(STDERR_FILENO, "Error:\nMissing ceiling color\n"),
			FAIL);
	else if (cub3d->floor_assigned == false)
		return (ft_printf(STDERR_FILENO, "Error:\nMissing floor color\n"),
			FAIL);
	else if (!cub3d->map)
		return (ft_printf(STDERR_FILENO, "Error:\nMissing map\n"), FAIL);
	return (SUCCESS);
}

/*
	file validation main function
*/
int	ft_file_validation(char *map_file, t_cub3d *cub3d)
{
	char	*line;
	int		fd;

	fd = 0;
	if (!ft_check_file_extensions(map_file, ".cub"))
		return (FAIL);
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return (ft_printf(STDERR_FILENO, "Error\nDoesn't exist file: %s\n",
				map_file), FAIL);
	line = ft_get_next_line(fd);
	while (line != NULL)
	{
		if (ft_line_analisis(line, cub3d) == FAIL)
			return (free(line), close(fd), FAIL);
		if (cub3d->map_started == true)
			return (ft_store_map_lines(fd, line, cub3d));
		free(line);
		line = ft_get_next_line(fd);
	}
	close(fd);
	return (ft_check_all(cub3d));
}

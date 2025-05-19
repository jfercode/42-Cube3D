/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:14:09 by jaferna2          #+#    #+#             */
/*   Updated: 2025/05/19 19:23:06 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	ft_assign_textures(char *cleaned, char flag, t_cub3d *cub3d)
{
	if (flag == 'N')
	{
		if (cub3d->wall_textures->north != NULL)	
			return (ft_printf(STDERR_FILENO, "Error:\nDuplicated NO texture\n"), FAIL);
		cub3d->wall_textures->north = ft_strdup(cleaned);
	}
	else if (flag == 'S')
	{
		if (cub3d->wall_textures->south != NULL)
			return (ft_printf(STDERR_FILENO, "Error:\nDuplicated SO texture\n"), FAIL);
		cub3d->wall_textures->south = ft_strdup(cleaned);
	}
	else if (flag == 'W')
	{
		if (cub3d->wall_textures->west != NULL)
			return (ft_printf(STDERR_FILENO, "Error:\nDuplicated WE texture\n"), FAIL);
		cub3d->wall_textures->west = ft_strdup(cleaned);
	}
	else if (flag == 'E')
	{
		if (cub3d->wall_textures->east != NULL)
			return (ft_printf(STDERR_FILENO, "Error:\nDuplicated EA texture\n"), FAIL);
		cub3d->wall_textures->east = ft_strdup(cleaned);
	}
	return (free(cleaned), SUCCESS);
}

int	ft_validate_texture_line(char *line, int i, char flag,
		t_cub3d *cub3d)
{
	int		fd;
	char	*cleaned;

	while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
		i++;
	cleaned = ft_strip_newline(&line[i]);
	if (!cleaned)
		return (FAIL);
	fd = open(cleaned, O_RDONLY);
	if (fd < 0)
		return (ft_printf(STDERR_FILENO, "Error:\nDoesn't exist file: %s\n",
				cleaned), FAIL);
	if (ft_check_file_extensions(cleaned, ".xpm"))
	{
		close(fd);
		if (ft_assign_textures(cleaned, flag, cub3d))
			return (SUCCESS);
		else
			return (free(cleaned), FAIL);
	}
	return (free (cleaned), FAIL);
}

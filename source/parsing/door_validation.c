/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:57:49 by jaferna2          #+#    #+#             */
/*   Updated: 2025/06/09 18:24:45 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	ft_validate_door_text(char *cleaned, char flag, t_cub3d *cub3d)
{
	if (flag == '0')
	{
		if (cub3d->door_texture[0] != NULL)
			return (ft_printf(STDERR_FILENO, "Error:\nDup D0 texture\n"), FAIL);
		cub3d->door_texture[0] = ft_strdup(cleaned);
	}
	else if (flag == '1')
	{
		if (cub3d->door_texture[1] != NULL)
			return (ft_printf(STDERR_FILENO, "Error:\nDup D1 texture\n"), FAIL);
		cub3d->door_texture[1] = ft_strdup(cleaned);
	}
	else if (flag == '2')
	{
		if (cub3d->door_texture[2] != NULL)
			return (ft_printf(STDERR_FILENO, "Error:\nDup D2 texture\n"), FAIL);
		cub3d->door_texture[2] = ft_strdup(cleaned);
	}
	else if (flag == '3')
	{
		if (cub3d->door_texture[3] != NULL)
			return (ft_printf(STDERR_FILENO, "Error:\nDup D3 texture\n"), FAIL);
		cub3d->door_texture[3] = ft_strdup(cleaned);
	}
	return (free(cleaned), SUCCESS);
}

int	ft_validate_door_line(char *line, int i, t_cub3d *cub3d)
{
	int		fd;
	char	flag;
	char	*cleaned;

	while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
		i++;
	flag = line[i];
	i++;
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
		if (ft_validate_door_text(cleaned, flag, cub3d))
			return (SUCCESS);
		else
			return (free(cleaned), FAIL);
	}
	return (free(cleaned), FAIL);
}

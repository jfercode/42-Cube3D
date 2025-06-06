/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:57:49 by jaferna2          #+#    #+#             */
/*   Updated: 2025/06/06 12:59:12 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	ft_validate_door_line(char *line, int i, t_cub3d *cub3d)
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
		if (cub3d->door_texture != NULL)
			return (ft_printf(STDERR_FILENO, "Error:\nDup D texture\n"), free(cleaned), FAIL);
		cub3d->door_texture = ft_strdup(cleaned);
		return (free(cleaned), SUCCESS);
	}
	return (free(cleaned), FAIL);
}

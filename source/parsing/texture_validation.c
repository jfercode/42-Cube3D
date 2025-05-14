/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:14:09 by jaferna2          #+#    #+#             */
/*   Updated: 2025/05/13 17:04:26 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static char	*ft_strip_newline(char *str)
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

int	ft_validate_texture_line(char *line, int i, char flag,
		t_cub3d *cub3d)
{
	int		fd;
	char	*cleaned;

	while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
		i++;
	cleaned = ft_strip_newline(&line[i]);
	fd = open(cleaned, O_RDONLY);
	if (fd < 0)
		return (ft_printf(STDERR_FILENO, "Error:\nDoesn't exist file: %s\n",
				cleaned), FAIL);
	if (ft_check_map_extensions(cleaned, ".xpm"))
	{
		close(fd);
		if (flag == 'N')
			cub3d->wall_textures->north = ft_strdup(cleaned);
		else if (flag == 'S')
			cub3d->wall_textures->south = ft_strdup(cleaned);
		else if (flag == 'W')
			cub3d->wall_textures->west = ft_strdup(cleaned);
		else if (flag == 'E')
			cub3d->wall_textures->east = ft_strdup(cleaned);
		return (free(cleaned), SUCCESS);
	}
	return (FAIL);
}


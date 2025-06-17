/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_closed_validation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:16:05 by jaferna2          #+#    #+#             */
/*   Updated: 2025/06/17 17:27:18 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static char	**ft_expand_map_02(char **map, int width, int height, int i)
{
	char	**new_map;

	new_map = malloc(sizeof(char *) * (height + 1));
	if (!new_map)
		return (NULL);
	while (i < height)
	{
		new_map[i] = ft_calloc(width + 1, sizeof(char));
		if (!new_map[i])
			return (ft_free_matrix(new_map), NULL);
		ft_memset(new_map[i], ' ', width);
		ft_memcpy(new_map[i], map[i], ft_strlen(map[i]));
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

static char	**ft_expand_map(char **map)
{
	int	width;
	int	height;
	int	i;

	width = 0;
	height = 0;
	i = 0;
	while (map[height])
	{
		if ((int)ft_strlen(map[height]) > width)
			width = ft_strlen(map[height]);
		height++;
	}
	return (ft_expand_map_02(map, width, height, i));
}

static int	ft_flood_fill(char **map, int x, int y)
{
	if (x < 0 || y < 0 || !map[y] || !map[y][x])
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'X')
		return (1);
	map[y][x] = 'X';
	return (ft_flood_fill(map, x + 1, y) && ft_flood_fill(map, x - 1, y)
		&& ft_flood_fill(map, x, y + 1) && ft_flood_fill(map, x, y - 1));
}

int	ft_map_is_finished(int fd)
{
	char	*line;

	line = ft_get_next_line(fd);
	if (line != NULL)
		return (ft_get_next_line(-4242), free(line), ft_printf(STDERR_FILENO,
				"Error:\nMap is not finished\n"), FAIL);
	else
		return (free(line), SUCCESS);
}

int	ft_check_map_closed(t_cub3d *cub3d)
{
	char	**map_copy;
	int		i;

	map_copy = ft_expand_map(cub3d->map);
	if (!map_copy)
		return (FAIL);
	i = ft_flood_fill(map_copy, cub3d->player_x, cub3d->player_y);
	ft_free_matrix(map_copy);
	if (i)
		return (SUCCESS);
	else
		return (ft_printf(STDERR_FILENO, "Error:\nMap is not closed\n"), FAIL);
}

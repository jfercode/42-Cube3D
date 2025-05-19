/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:51:49 by jaferna2          #+#    #+#             */
/*   Updated: 2025/05/19 17:22:40 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	ft_check_valid_map_chars(char **map)
{
	int			i;
	int			j;
	const char	*valid = "01NSEW ";
	
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!ft_strchr(valid, map[i][j]))
				return(ft_printf(STDERR_FILENO,
					"Error;\nInvalid character %c in map\n", map[i][j]), FAIL);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

static int	ft_check_single_player(t_cub3d *cub3d)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (cub3d->map[i])
	{
		j = 0;
		while (cub3d->map[i][j])
		{
			if (ft_strchr("NSEW", cub3d->map[i][j]))
			{
				cub3d->player_dir = cub3d->map[i][j];
				cub3d->player_x = j;
				cub3d->player_y = i;
				count++;
			}
			j++;
		}
		i++;
	}
	if (count != 1)
		return (ft_printf(STDERR_FILENO, "Error:\nInvalid number of player position (%d)\n", count), FAIL);
	return (SUCCESS);
}

int	ft_map_validation(t_cub3d *cub3d)
{
	if (ft_check_valid_map_chars(cub3d->map) == FAIL)
		return (FAIL);
	if (ft_check_single_player(cub3d) == FAIL)
		return (FAIL);
	if (ft_check_map_closed(cub3d) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
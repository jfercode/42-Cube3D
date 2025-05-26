/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:39:24 by jaferna2          #+#    #+#             */
/*   Updated: 2025/05/26 16:26:11 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	ft_turn_on_color_bool(t_cub3d *cub3d, char flag)
{
	if (flag == 'C')
	{
		cub3d->ceiling_assigned = true;
		return (SUCCESS);
	}
	else if (flag == 'F')
	{
		cub3d->floor_assigned = true;
		return (SUCCESS);
	}
	else
		return (FAIL);
}

static int	ft_assign_color(char *cleaned, char flag, t_cub3d *cub3d)
{
	char	**color_mtx;
	int		temp;
	int		i;

	color_mtx = ft_split(cleaned, ',');
	if (ft_matrix_len(color_mtx) != 3)
		return (ft_printf(STDERR_FILENO, "Error:\nInvalid %c color argument\n",
				flag), ft_free_matrix(color_mtx), FAIL);
	i = 0;
	while (color_mtx[i])
	{
		temp = ft_atoi(color_mtx[i]);
		if (temp < 0 || temp > 255)
			return (ft_printf(STDERR_FILENO, "Error:\nInvalid value %d in "
					"%c argument\n", temp, flag), ft_free_matrix(color_mtx), 1);
		else
		{
			if (flag == 'C')
				cub3d->ceiling_rgb[i] = temp;
			else if (flag == 'F')
				cub3d->floor_rgb[i] = temp;
		}
		i++;
	}
	return (ft_free_matrix(color_mtx), ft_turn_on_color_bool(cub3d, flag));
}

int	ft_validate_color_line(char *line, int i, char flag,
		t_cub3d *cub3d)
{
	char	*cleaned;
	int		result;

	while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
		i++;
	cleaned = ft_strip_newline(&line[i]);
	if (flag == 'C')
	{
		if (cub3d->ceiling_assigned == true)
			return (ft_printf(STDOUT_FILENO, "Error:\nDuplicated C color"),
				FAIL);
	}
	else if (flag == 'F')
	{
		if (cub3d->floor_assigned == true)
			return (ft_printf(STDOUT_FILENO, "Error:\nDuplicated F color\n"),
				FAIL);
	}
	result = ft_assign_color(cleaned, flag, cub3d);
	return (free(cleaned), result);
}

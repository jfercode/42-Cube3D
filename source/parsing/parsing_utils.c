/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:56:05 by jaferna2          #+#    #+#             */
/*   Updated: 2025/06/09 18:22:05 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	ft_print_map(char **map)
{
	int	i;

	i = 0;
	ft_printf(STDOUT_FILENO, GREEN "[Map]\n" RST);
	while (map[i])
	{
		ft_printf(STDOUT_FILENO, "%s\n", map[i]);
		i++;
	}
}

static void	ft_print_door(t_cub3d *cub3d)
{
	if (cub3d->door_texture[0])
		ft_printf(STDOUT_FILENO, GREEN "[Door 0]" RST " %s\n",
			cub3d->door_texture[0]);
	if (cub3d->door_texture[1])
		ft_printf(STDOUT_FILENO, GREEN "[Door 1]" RST " %s\n",
			cub3d->door_texture[1]);
	if (cub3d->door_texture[2])
		ft_printf(STDOUT_FILENO, GREEN "[Door 2]" RST " %s\n",
			cub3d->door_texture[2]);
	if (cub3d->door_texture[3])
		ft_printf(STDOUT_FILENO, GREEN "[Door 0]" RST " %s\n",
			cub3d->door_texture[3]);
}

void	ft_print_cub3d(t_cub3d *cub3d)
{
	ft_printf(STDOUT_FILENO, GREEN "DEBUGING CUB3D\n" RST);
	if (cub3d->floor_assigned && cub3d->ceiling_assigned)
	{
		ft_printf(STDOUT_FILENO, GREEN "[Floor]" RST " %d, %d, %d\n",
			cub3d->floor_rgb[0], cub3d->floor_rgb[1], cub3d->floor_rgb[2]);
		ft_printf(STDOUT_FILENO, GREEN "[Ceiling]" RST " %d, %d, %d\n",
			cub3d->ceiling_rgb[0], cub3d->ceiling_rgb[1],
			cub3d->ceiling_rgb[2]);
	}
	if (cub3d->wall_textures->north)
		ft_printf(STDOUT_FILENO, GREEN "[North]" RST " %s\n",
			cub3d->wall_textures->north);
	if (cub3d->wall_textures->south)
		ft_printf(STDOUT_FILENO, GREEN "[South]" RST " %s\n",
			cub3d->wall_textures->south);
	if (cub3d->wall_textures->east)
		ft_printf(STDOUT_FILENO, GREEN "[East]" RST " %s\n",
			cub3d->wall_textures->east);
	if (cub3d->wall_textures->west)
		ft_printf(STDOUT_FILENO, GREEN "[West]" RST " %s\n",
			cub3d->wall_textures->west);
	if (IS_BONUS == 1)
		ft_print_door(cub3d);
	if (cub3d->map)
		ft_print_map(cub3d->map);
}

/*	Strip the newline (\n) character from a line */
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
	if (!cleaned)
		return (NULL);
	return (cleaned);
}

/* Check the map extension */
int	ft_check_file_extensions(char *map_file_name, char *extension)
{
	char	*file_extension;

	file_extension = ft_strrchr(map_file_name, '.');
	if (!file_extension)
		return (ft_printf(STDERR_FILENO, "Error:\nNo extension: %s\n",
				map_file_name), FAIL);
	else if (ft_strncmp(file_extension, extension, ft_strlen(extension)))
		return (ft_printf(STDERR_FILENO, "Error:\nWrong extension: %s\n",
				map_file_name), FAIL);
	return (SUCCESS);
}

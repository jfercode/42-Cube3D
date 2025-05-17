/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 <jaferna2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 16:56:05 by jaferna2          #+#    #+#             */
/*   Updated: 2025/05/17 16:56:43 by jaferna2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/cub3D.h"

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

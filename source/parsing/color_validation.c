/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaferna2 < jaferna2@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:39:24 by jaferna2          #+#    #+#             */
/*   Updated: 2025/05/13 17:06:23 by jaferna2         ###   ########.fr       */
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
int ft_check_color(char *cleaned_line)
{
    // TO DO CHECK 3 COLORS, SPLITTED BY , AND NO NEGATIVES
}
int	ft_validate_color_line(char *line, int i, char flag,
		t_cub3d *cub3d)
{
	int		fd;
	char	*cleaned;

	while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
		i++;
	cleaned = ft_strip_newline(&line[i]);
    if (ft_check_color(cleaned))
    {
        if (flag == 'C')
            cub3d->ceiling_color = ft_strdup(cleaned);
        else if (flag == 'F')
            cub3d->ceiling_color = ft_strdup(cleaned);
        return (SUCCESS);
    }
	return (free(cleaned), FAIL);
}

int	ft_line_check_color(char *line, int i, t_cub3d *cub3d)
{
	if (ft_strncmp("C", line, 1))
        
		
	return (FAIL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_storation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:55:55 by jaferna2          #+#    #+#             */
/*   Updated: 2025/06/17 17:25:45 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	ft_is_line_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

static char	**ft_lst_to_mtx(t_list *lst, char **mtx)
{
	int	len;
	int	i;

	len = ft_lstsize(lst);
	mtx = malloc(sizeof(char *) * (len + 1));
	if (!mtx)
		return (NULL);
	i = 0;
	while (lst)
	{
		mtx[i] = ft_strdup((char *)lst->content);
		lst = lst->next;
		i++;
	}
	mtx[i] = NULL;
	return (mtx);
}

int	ft_store_map_lines(int fd, char *first_line, t_cub3d *cub3d)
{
	char	*line;
	t_list	*map_lines;

	map_lines = NULL;
	ft_lstadd_back(&map_lines, ft_lstnew(ft_strip_newline(first_line)));
	free(first_line);
	line = ft_get_next_line(fd);
	while (line != NULL)
	{
		if (ft_is_line_empty(line))
		{
			free(line);
			break ;
		}
		ft_lstadd_back(&map_lines, ft_lstnew(ft_strip_newline(line)));
		free(line);
		line = ft_get_next_line(fd);
	}
	cub3d->map = ft_lst_to_mtx(map_lines, cub3d->map);
	ft_lstclear(&map_lines, free);
	if (!cub3d->map)
		return (ft_printf(STDERR_FILENO, "Error:\nMap allocation failed\n"),
			FAIL);
	return (ft_map_validation(cub3d));
}

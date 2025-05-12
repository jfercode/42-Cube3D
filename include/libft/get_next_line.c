/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:15:24 by penpalac          #+#    #+#             */
/*   Updated: 2025/03/18 18:10:44 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*readfd(int fd, char *holder)
{
	int		readbytes;
	char	*buffer;

	readbytes = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free(&holder));
	buffer[0] = '\0';
	while (readbytes > 0 && !ft_strchr(buffer, '\n'))
	{
		readbytes = read (fd, buffer, BUFFER_SIZE);
		if (readbytes > 0)
		{
			buffer[readbytes] = '\0';
			holder = ft_strjoin(holder, buffer);
		}
	}
	free(buffer);
	if (readbytes == -1)
		return (ft_free(&holder));
	return (holder);
}

char	*next_line(char *holder)
{
	char	*next;
	char	*tmp;
	int		len;

	tmp = ft_strchr(holder, '\n');
	if (!tmp)
	{
		next = NULL;
		return (ft_free(&holder));
	}
	else
		len = (tmp - holder) + 1;
	if (!holder[len])
		return (ft_free(&holder));
	next = ft_substr(holder, len, ft_strlen(holder) - len);
	ft_free(&holder);
	if (!next)
		return (NULL);
	return (next);
}

char	*get_next_line(int fd)
{
	static char	*holder;
	char		*line;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!holder || (holder && !ft_strchr(holder, '\n')))
		holder = readfd(fd, holder);
	if (!holder)
		return (NULL);
	tmp = ft_strchr(holder, '\n');
	line = ft_substr(holder, 0, (tmp - holder) + 1);
	if (!line)
		return (ft_free(&holder));
	holder = next_line(holder);
	return (line);
}

/*
int	main(void)
{
	int	fd;
	char	*line;
	int	i = 0;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%d: %s", i, line);
		free(line);
		i++;
	}
	close (fd);
	return (0);
}
*/

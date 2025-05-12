/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:17:08 by penpalac          #+#    #+#             */
/*   Updated: 2025/03/18 18:10:38 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	gnl_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*gnl_strchr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	if (c == '\0')
		return (&s[i]);
	return (0);
}

void	*gnl_calloc(size_t nmemb, size_t size)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)malloc (nmemb * size);
	if (!ptr)
		return (NULL);
	while (i < (nmemb * size))
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		c;

	if (!s1)
	{
		s1 = malloc(sizeof(char) + 1);
		if (!s1)
			return (0);
		s1[0] = 0;
	}
	s3 = gnl_calloc(gnl_strlen(s1) + gnl_strlen(s2) + 1, sizeof(char));
	if (!s3)
		return (gnl_free(&s1));
	i = -1;
	while (s1[++i])
		s3[i] = s1[i];
	c = -1;
	while (s2[++c])
		s3[i + c] = s2[c];
	free(s1);
	return (s3);
}

char	*gnl_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	strlen;
	char	*mem;

	i = 0;
	strlen = gnl_strlen(s);
	if (start >= strlen)
		return ((char *)gnl_calloc(1, sizeof(char)));
	if (len > (strlen - start))
		len = strlen - start;
	mem = (char *)malloc(len + 1);
	if (!mem)
		return (NULL);
	while (i < len)
	{
		mem[i] = s[start + i];
		i++;
	}
	mem[i] = '\0';
	return (mem);
}

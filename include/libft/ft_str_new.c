/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:19:14 by penpalac          #+#    #+#             */
/*   Updated: 2025/03/18 18:27:38 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*dup;
	size_t	i;

	i = 0;
	dup = (char *) malloc(ft_strlen(src) + 1);
	if (!dup)
		return (NULL);
	while (src[i] != '\0')
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srcsize;

	srcsize = 0;
	while (src[srcsize] != '\0')
		srcsize++;
	if (srcsize + 1 < size)
		ft_memcpy(dst, src, srcsize + 1);
	else if (size)
	{
		ft_memcpy(dst, src, size - 1);
		dst[size - 1] = 0;
	}
	return (srcsize);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	n;
	unsigned int	destsize;
	unsigned int	srcsize;

	i = 0;
	while (dst[i] != '\0')
		i++;
	destsize = i;
	j = 0;
	while (src[j] != '\0')
		j++;
	srcsize = j;
	if (destsize > size)
		return (size + srcsize);
	n = 0;
	while ((src[n] != '\0') && (i + 1 < size))
	{
		dst[i] = src[n];
		n++;
		i++;
	}
	dst[i] = '\0';
	return (destsize + j);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		i;

	i = 0;
	s3 = (char *)malloc (ft_strlen(s1) + ft_strlen(s2) + 1);
	if (s3 == NULL)
		return (NULL);
	while (*s1)
	{
		s3[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		s3[i] = *s2;
		i++;
		s2++;
	}
	s3[i] = '\0';
	return (s3);
}

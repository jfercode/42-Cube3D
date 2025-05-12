/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:56:26 by penpalac          #+#    #+#             */
/*   Updated: 2025/03/18 18:23:52 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		if (s1[i] == '\0' || s2[i] == '\0')
			i = n + 1;
		i++;
	}
	return (0);
}

char	*ft_strchr(char *s, int c)
{
	c = (char)c;
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	if (*s == c)
		return (s);
	return (NULL);
}

char	*ft_strrchr(char *s, int c)
{
	char	*ch;

	ch = NULL;
	c = (char)c;
	while (*s)
	{
		if (*s == c)
			ch = s;
		s++;
	}
	if (*s == c)
		ch = s;
	return (ch);
}

char	*ft_strnstr(char *big, char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*little == '\0')
		return (big);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && i + j < len)
		{
			if (little[j] == '\0')
				return (&big[i]);
			j++;
		}
		if (little[j] == '\0')
			return (&big[i]);
		i++;
	}
	return (NULL);
}

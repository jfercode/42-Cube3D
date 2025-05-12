/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:49:51 by penpalac          #+#    #+#             */
/*   Updated: 2024/09/25 15:59:24 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_strs(char **strs, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

static char	*makesub( char *str, int start, int end)
{
	int		len;
	int		i;
	char	*substr;

	i = 0;
	len = end - start;
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	while (i < len)
	{
		substr[i] = str[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

static char	**mejorsplit(char *s, char c, char **strs, int start)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] != '\0' && (s[i] == c))
			i++;
		start = i;
		while (s[i] != '\0' && !(s[i] == c))
			i++;
		if (i > start)
		{
			strs[j] = makesub(s, start, i);
			if (!strs[j])
			{
				free_strs(strs, j);
				return (NULL);
			}
			j++;
		}
	}
	strs[j] = NULL;
	return (strs);
}

static int	countwords(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		words;
	int		start;

	if (!s)
		return (NULL);
	words = countwords(s, c);
	strs = (char **)malloc ((words + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	start = 0;
	strs = mejorsplit((char *)s, c, strs, start);
	return (strs);
}

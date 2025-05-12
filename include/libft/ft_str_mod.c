/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_mod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:47:07 by penpalac          #+#    #+#             */
/*   Updated: 2025/03/18 18:26:19 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	strlen;
	char	*mem;

	i = 0;
	strlen = ft_strlen(s);
	if (start >= strlen)
		return ((char *)ft_calloc(1, sizeof(char)));
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

static int	inset(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	int		lenstr;
	char	*corte;

	lenstr = ft_strlen(s1);
	start = 0;
	end = lenstr - 1;
	i = 0;
	while (s1[start] && inset(s1[start], set))
		start++;
	while (end >= start && inset(s1[end], set))
		end--;
	corte = (char *)malloc((end - start + 1) + 1);
	if (!corte)
		return (NULL);
	while (start <= end)
	{
		corte[i] = s1[start];
		i++;
		start++;
	}
	corte[i] = '\0';
	return (corte);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*newstr;
	int		i;

	i = 0;
	newstr = (char *)malloc ((ft_strlen(s) + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	while (s[i] != '\0')
	{
		newstr[i] = f(i, s[i]);
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		(*f)(i, &s[i]);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simple_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:30:35 by penpalac          #+#    #+#             */
/*   Updated: 2025/03/18 18:29:00 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t mem, size_t size)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)malloc(mem * size);
	if (!ptr)
		return (NULL);
	while (i < (mem * size))
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	else
		return (c);
}

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	else
		return (c);
}

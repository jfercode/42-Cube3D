/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:25:11 by penpalac          #+#    #+#             */
/*   Updated: 2025/03/18 18:19:48 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*ch;

	i = 0;
	ch = (char *)s;
	c = (char)c;
	while (i < n)
	{
		if (ch[i] == c)
			return (&ch[i]);
		i++;
	}
	return (NULL);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*cast;

	i = 0;
	cast = (char *)s;
	while (i < n)
	{
		cast[i] = c;
		i++;
	}
	return (cast);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*cd;
	char	*cs;

	if (!dest && !src)
		return (NULL);
	cd = (char *)dest;
	cs = (char *)src;
	if (cd < cs || cd >= cs + n)
	{
		while (n--)
			*cd++ = *cs++;
	}
	else
	{
		cd += n;
		cs += n;
		while (n--)
			*(--cd) = *(--cs);
	}
	return (dest);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*memdst;
	char	*memsrc;
	size_t	i;

	memdst = (char *)dest;
	memsrc = (char *)src;
	if (!memdst && !memsrc)
		return (memdst);
	i = 0;
	while (i < n)
	{
		memdst[i] = memsrc[i];
		i++;
	}
	return (memdst);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*cs1;
	unsigned char	*cs2;

	i = 0;
	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	while (i < n)
	{
		if (cs1[i] != cs2[i])
			return (cs1[i] - cs2[i]);
		i++;
	}
	return (0);
}

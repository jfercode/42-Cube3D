/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:50:40 by penpalac          #+#    #+#             */
/*   Updated: 2024/12/16 12:26:36 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		getlen(int n)
{
	int i;

	if (n == 0)
		return (1);
	i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		sign;
	int		len;
	char	*nbr;

	len = getlen(n);
	if(n < 0)
	{
		sign = -1;
		n *= -1;
		len++;
	}
	nbr = (char *)malloc((len + 1) * sizeof(char));
	if (!nbr)
		return (NULL);
	nbr[0] = '-';
	nbr[len] = '\0';
	while ((len - 1) >= 0)
	{
		nbr[len - 1] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	return (nbr);
}

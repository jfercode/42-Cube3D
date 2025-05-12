/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:08:02 by penpalac          #+#    #+#             */
/*   Updated: 2025/05/12 18:53:55 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_putnbr(signed int n, int cont)
{
	char	c;

	if (n == -2147483648)
		cont = ft_putstr("-2147483648", cont);
	else
	{
		if (n < 0)
		{
			cont = ft_putchar ('-', cont);
			n *= -1;
			cont = ft_putnbr (n, cont);
		}
		else if (n > 9)
		{
			cont = ft_putnbr (n / 10, cont);
			cont = ft_putnbr (n % 10, cont);
		}
		else
		{
			c = '0' + n;
			write (1, &c, 1);
			cont++;
		}
	}
	return (cont);
}

int	print_putunsnbr(unsigned int n, int cont)
{
	char	c;

	if (n > 9)
	{
		cont = ft_putnbr (n / 10, cont);
		cont = ft_putnbr (n % 10, cont);
	}
	else
	{
		c = '0' + n;
		write (1, &c, 1);
		cont++;
	}
	return (cont);
}

int	print_putptr(unsigned long long n, char *base, int cont, int flag)
{
	unsigned long long	size;
	unsigned long long	num;

	if (!n)
	{
		cont = ft_putstr ("(nil)", cont);
		return (cont);
	}
	num = n;
	size = ft_strlen (base);
	if (flag)
		cont = ft_putstr ("0x", cont);
	if (num < 0)
		num *= -1;
	if (num >= size)
		cont = ft_putptr (n / size, base, cont, 0);
	write(1, &base[num % size], 1);
	cont++;
	return (cont);
}

int	print_puthex(unsigned int nbr, char *base, int cont)
{
	long	size;
	long	num;

	num = nbr;
	size = ft_strlen (base);
	if (num >= size)
		cont = ft_puthex (num / size, base, cont);
	write(1, &base[num % size], 1);
	cont++;
	return (cont);
}


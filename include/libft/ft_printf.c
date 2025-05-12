/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:55:42 by penpalac          #+#    #+#             */
/*   Updated: 2025/03/18 18:13:35 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	getfunc(char c, va_list arg, int cont)
{
	if (c == 'd' || c == 'i')
		cont = ft_putnbr (va_arg(arg, int), cont);
	else if (c == 'u')
		cont = ft_putunsnbr (va_arg(arg, int), cont);
	else if (c == 'c')
		cont = ft_putchar (va_arg(arg, int), cont);
	else if (c == 's')
		cont = ft_putstr (va_arg(arg, char *), cont);
	else if (c == 'p')
		cont = ft_putptr (va_arg(arg, unsigned long), "0123456789abcdef",
				cont, 1);
	else if (c == 'x')
		cont = ft_puthex (va_arg(arg, unsigned int), "0123456789abcdef", cont);
	else if (c == 'X')
		cont = ft_puthex (va_arg(arg, int), "0123456789ABCDEF", cont);
	else if (c == '%')
		cont = ft_putchar('%', cont);
	return (cont);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	int		i;
	int		cont;

	va_start(arg, format);
	i = 0;
	cont = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			i++;
			cont = getfunc(format[i], arg, cont);
		}
		else
			cont = ft_putchar (format[i], cont);
		i++;
	}
	va_end(arg);
	return (cont);
}

int	ft_putchar(char c, int cont)
{
	write (1, &c, 1);
	cont++;
	return (cont);
}

int	ft_putstr(char *s, int cont)
{
	int	i;

	if (!s)
	{
		cont = ft_putstr("(null)", cont);
		return (cont);
	}
	i = 0;
	while (s[i])
	{
		write (1, &s[i], 1);
		i++;
		cont++;
	}
	return (cont);
}

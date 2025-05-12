/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_issth.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:33:29 by penpalac          #+#    #+#             */
/*   Updated: 2025/03/18 18:18:36 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) && ft_isdigit(c))
		return (1);
	else
		return (0);
}

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (c);
	else
		return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90))
		return (1);
	else
		return (0);
}

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c < 58)
		return (1);
	else
		return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penpalac <penpalac@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:54:29 by penpalac          #+#    #+#             */
/*   Updated: 2025/03/18 18:22:01 by penpalac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst != NULL)
	{
		del (lst->content);
		free (lst);
	}
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*brr;

	if (!lst || !del)
		return ;
	while (*lst != NULL)
	{
		brr = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = brr;
	}
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	last = ft_lstlast(*lst);
	if (!last)
	{
		*lst = new;
		return ;
	}
	last->next = new;
}

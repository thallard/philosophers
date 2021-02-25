/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:42:46 by thallard          #+#    #+#             */
/*   Updated: 2021/02/25 16:03:25 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

t_malloc	*ft_lstnew(void *content)
{
	t_malloc	*elem;

	if (!(elem = malloc(sizeof(t_malloc))))
		return (NULL);
	elem->content = content;
	elem->next = NULL;
	return (elem);
}

t_malloc	*ft_lstlast(t_malloc *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_malloc **alst, t_malloc *new)
{
	t_malloc	*elem;

	if (!(*alst))
		*alst = new;
	else
	{
		elem = ft_lstlast(*alst);
		elem->next = new;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_free_and_exit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:10:08 by thallard          #+#    #+#             */
/*   Updated: 2021/02/25 16:03:49 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*lst_malloc(int size, t_global *global)
{
	void		*ptr;

	if (!(ptr = malloc(size)))
		ft_exit(global);
	if (!(add_lst_to_free(global, ptr)))
		ft_exit(global);
	return (ptr);
}

void	*add_lst_to_free(t_global *global, void *ptr)
{
	t_malloc	*new;

	if (!(new = ft_lstnew(ptr)))
	{
		free(ptr);
		return (NULL);
	}
	ft_lstadd_back(&global->lst_free, new);
	return (ptr);
}


void	ft_exit(t_global *global)
{
	printf("crash\n");
	exit(0);
}
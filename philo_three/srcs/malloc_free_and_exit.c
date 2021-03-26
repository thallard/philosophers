/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_free_and_exit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:53:01 by thallard          #+#    #+#             */
/*   Updated: 2021/03/26 15:20:53 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void	*malloc_lst(int size, t_global *global)
{
	void		*ptr;

	if (!(ptr = malloc(size)))
		return (NULL);
	if (!(add_lst_to_free(global, ptr)))
		return (NULL);
	return (ptr);
}

void	*add_lst_to_free(t_global *global, void *ptr)
{
	t_malloc	*new;

	if (!(new = ft_lstmalloc_new(ptr)))
	{
		free(ptr);
		return (NULL);
	}
	ft_lstmalloc_add_back(&global->lst_free, new);
	return (ptr);
}

int	error_malloc(t_global *g, int freeall)
{
	if (freeall)
		ft_lstmalloc_clear(&g->lst_free, free, g);
	printf("\e[31mError : A malloc has failed.\e[0m\n");
	return (0);
}
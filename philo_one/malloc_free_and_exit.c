/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_free_and_exit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:10:08 by thallard          #+#    #+#             */
/*   Updated: 2021/02/27 15:44:35 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*malloc_lst(int size, t_global *global)
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
	printf("crash ici ma couille: %ld\n", global->info->nb_philo);
	exit(0);
}

void	ft_fin(t_global *g, int pos)
{
	(void)g;
	printf("Fin du programme un philosophe est mort : %d\n", pos);
	exit(0);
}
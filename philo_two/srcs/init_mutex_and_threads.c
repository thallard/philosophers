/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex_and_threads.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:00:28 by thallard          #+#    #+#             */
/*   Updated: 2021/03/26 13:34:22 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

pthread_t	ft_create_thread(t_global *global)
{
	pthread_t	thread;

	thread = malloc_lst(sizeof(pthread_t), global);
	if (!thread)
		return (NULL);
	return (thread);
}

int	ft_fill_threads(t_global *global)
{
	int		i;

	i = -1;
	global->threads = malloc_lst(sizeof(pthread_t) 
			 * (global->info->nb_philo + 2000), global);
	if (!global->threads)
		return (0);
	while (++i < global->info->nb_philo)
		global->threads[i] = ft_create_thread(global);
	global->threads[i] = NULL;
	return (1);
}

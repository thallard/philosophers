/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex_and_threads.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:00:28 by thallard          #+#    #+#             */
/*   Updated: 2021/03/26 11:20:21 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

pthread_mutex_t	ft_create_fork(t_global *g)
{
	pthread_mutex_t		mutex;

	(void)g;
	if (pthread_mutex_init(&mutex, NULL))
		return (mutex);
	return (mutex);
}

int	ft_fill_forks(t_global *g)
{
	int		i;

	i = -1;
	g->forks = malloc_lst(sizeof(pthread_mutex_t) * (g->info->nb_philo + 1), g);
	if (!g->forks)
		return (0);
	while (++i < g->info->nb_philo)
		g->forks[i] = ft_create_fork(g);
	return (1);
}

pthread_mutex_t	*ft_fill_mutex(t_global *g)
{
	int				i;
	pthread_mutex_t	*forks;

	i = -1;
	forks = malloc_lst(sizeof(pthread_mutex_t) * (g->info->nb_philo + 1), g);
	if (!forks)
		return (NULL);
	while (++i < g->info->nb_philo)
		forks[i] = ft_create_fork(g);
	return (forks);
}

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
	global->threads = malloc_lst(sizeof(pthread_t) \
			 * (global->info->nb_philo + 2), global);
	if (!global->threads)
		return (0);
	while (++i < global->info->nb_philo)
		global->threads[i] = ft_create_thread(global);
	global->threads[i] = NULL;
	return (1);
}

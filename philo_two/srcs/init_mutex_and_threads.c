/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex_and_threads.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:00:28 by thallard          #+#    #+#             */
/*   Updated: 2021/03/25 17:13:21 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

// pthread_mutex_t	ft_create_fork(t_global *g)
// {
// 	pthread_mutex_t		mutex;

// 	if (pthread_mutex_init(&mutex, NULL))
// 		ft_exit(g);
// 	return (mutex);
// }

// int	ft_fill_forks(t_global *g)
// {
// 	int		i;

// 	i = -1;
// 	g->forks = malloc_lst(sizeof(pthread_mutex_t) * (g->info->nb_philo + 1), g);
// 	if (!g->forks)
// 		ft_exit(g);
// 	while (++i < g->info->nb_philo)
// 		g->forks[i] = ft_create_fork(g);
// 	return (0);
// }

// pthread_mutex_t	*ft_fill_mutex(t_global *g)
// {
// 	int				i;
// 	pthread_mutex_t	*forks;

// 	i = -1;
// 	forks = malloc_lst(sizeof(pthread_mutex_t) * (g->info->nb_philo + 1), g);
// 	if (!forks)
// 		ft_exit(g);
// 	while (++i < g->info->nb_philo)
// 		forks[i] = ft_create_fork(g);
// 	return (forks);
// }

pthread_t	ft_create_thread(t_global *global)
{
	pthread_t	thread;

	thread = malloc_lst(sizeof(pthread_t), global);
	if (!thread)
		ft_exit(global);
	return (thread);
}

int	ft_fill_threads(t_global *global)
{
	int		i;

	i = -1;
	global->threads = malloc_lst(sizeof(pthread_t) 
			 * (global->info->nb_philo + 2000), global);
	if (!global->threads)
		ft_exit(global);
	while (++i < global->info->nb_philo)
		global->threads[i] = ft_create_thread(global);
	global->threads[i] = NULL;
	return (1);
}

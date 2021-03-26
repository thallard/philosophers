/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:39:20 by thallard          #+#    #+#             */
/*   Updated: 2021/03/26 15:48:56 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_one.h"

void	*main_loop(void *ptr)
{
	t_philos	*p;

	p = ptr;
	while (1)
	{
		if (p->tdie <= ft_time_p(p, 1))
			return (NULL);
		ft_take_forks(p);
		if (p->times_eat >= p->info->nb_eat && p->info->nb_eat != -1)
			return (NULL);
		ft_sleep(p);
		ft_think(p);
	}
	return (NULL);
}

int	loop_until_end_or_dead(t_global *global, t_infos_philo *info)
{
	int		i;
	int		eat;

	while (1)
	{
		i = -1;
		eat = 0;
		while (++i < info->nb_philo)
		{
			if (global->philos[i]->times_eat == info->nb_eat)
				eat++;
			if (global->philos[i]->tdie < ft_time_g(global, 1))
			{
				printf("\e[33m%.f \e[96m%d \033[0;31mdied\e[39m\n", \
				ft_time_g(global, 1), i + 1);
				pthread_mutex_lock(&global->mutex);
				return (ft_lstmalloc_clear(&global->lst_free, free, global));
			}
			if (eat == info->nb_philo)
			{
				pthread_mutex_lock(&global->mutex);
				return (ft_lstmalloc_clear(&global->lst_free, free, global));
			}
		}
	}
}

int	launch_routine(t_global *g, t_infos_philo *inf)
{
	int				i;
	struct timeval	tv;

	i = -1;
	ft_fill_threads(g);
	pthread_mutex_init(&g->mutex, NULL);
	g->forks = ft_fill_mutex(g);
	g->philos = malloc_lst(sizeof(t_philos *) * (inf->nb_philo + 1), g);
	if (!g->philos)
		return (error_malloc(g, 1));
	while (++i < inf->nb_philo)
	{
		gettimeofday(&tv, NULL);
		g->start_usec = tv.tv_usec;
		g->start_sec = tv.tv_sec;
		g->philos[i] = ft_init_philos(g, i);
		pthread_mutex_init(&(g->philos[i]->mutex), NULL);
		pthread_create(&g->philos[i]->thread, NULL, main_loop, \
			(void *)g->philos[i]);
		pthread_detach(g->philos[i]->thread);
		pthread_join(g->philos[i]->thread, NULL);
		usleep(20);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_infos_philo	*info;
	t_global		*global;

	global = malloc(sizeof(t_global));
	if (!global)
		return (error_malloc(NULL, 0));
	global->lst_free = NULL;
	info = malloc_lst(sizeof(t_infos_philo), global);
	if (!info)
		return (error_malloc(global, 1));
	if (argc > 6 || argc <= 4 )
	{
		printf("\e[33mError : Invalid number of parameters.\e[0m\n");
		return (ft_lstmalloc_clear(&global->lst_free, free, global));
	}
	if (!ft_init_infos_philo(info, global, argv, argc))
		return (ft_lstmalloc_clear(&global->lst_free, free, global));
	if (!launch_routine(global, info))
		return (ft_lstmalloc_clear(&global->lst_free, free, global));
	loop_until_end_or_dead(global, info);
}

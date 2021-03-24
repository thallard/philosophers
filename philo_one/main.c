/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:39:20 by thallard          #+#    #+#             */
/*   Updated: 2021/03/24 16:43:47 by thallard         ###   ########lyon.fr   */
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

void		launch_routine(t_global *g, t_infos_philo *inf)
{
	int				i;
	struct timeval	tv;

	i = -1;
	ft_fill_threads(g);
	pthread_mutex_init(&g->mutex, NULL);
	g->forks = ft_fill_mutex(g);
	g->philos = malloc_lst(sizeof(t_philos *) * (inf->nb_philo + 1), g);
	while (++i < inf->nb_philo)
	{
		gettimeofday(&tv, NULL);
		g->start_usec = tv.tv_usec;
		g->start_sec = tv.tv_sec;
		g->philos[i] = ft_init_philos(g, i);
		pthread_mutex_init(&(g->philos[i]->mutex), NULL);
		pthread_create(&g->philos[i]->thread, NULL, main_loop, (void *)g->philos[i]);
		pthread_detach(g->philos[i]->thread);
		pthread_join(g->philos[i]->thread, NULL);
		usleep(20);
	}
}

int loop_until_end_or_dead(t_global *global, t_infos_philo *info)
{
	int i;
	int eat;

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
				printf("\e[33m%.f \e[96m%d \033[0;31mdied\e[39m\n", ft_time_g(global, 1), i + 1);
				pthread_mutex_lock(&global->mutex);
				ft_lstmalloc_clear(&global->lst_free, free);
				return (0);
			}
			if (eat == info->nb_philo)
			{
				printf("fini de manger tout plein la\n");
				pthread_mutex_lock(&global->mutex);
				ft_lstmalloc_clear(&global->lst_free, free);
				return (0);
			}
		}
	}
}

int main(int argc, char **argv)
{
	t_infos_philo *info;
	t_global *global;

	global = malloc(sizeof(t_global));
	global->lst_free = NULL;
	add_lst_to_free(global, (void*)global);
	info = malloc_lst(sizeof(t_infos_philo), global);
	

	if (argc > 6 || argc <= 4)
	{
		printf("\e[33mError : Invalid number of parameters.\e[0m\n");
		return (0);
	}
	if (!ft_init_infos_philo(info, global, argv, argc))
		return (0);

	launch_routine(global, info);
	loop_until_end_or_dead(global, info);

	// dprintf(1, "[%ld] [%ld] [%ld] [%ld] [%ld]\n", global->info->nb_philo, info->time_die, info->time_eat, info->time_sleep, info->nb_eat);
}
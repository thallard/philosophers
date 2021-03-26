/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:39:20 by thallard          #+#    #+#             */
/*   Updated: 2021/03/26 13:51:48 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_two.h"

int		quit_program(t_global *g)
{
	int		i;

	sem_close(g->forks);
	sem_close(g->sem);
	i = -1;
	while (++i < g->info->nb_philo)
		sem_close(g->philos[i]->sem);
	sem_unlink("global");
	sem_unlink("fork");
	sem_unlink("philo");
	return (0);
}

void	*main_loop(void *ptr)
{
	t_philos	*p;

	p = ptr;
	while (1)
	{
		ft_think(p);
		if (p->tdie <= ft_time_p(p, 1))
			return (NULL);
		ft_take_forks(p);
		if (p->times_eat >= p->info->nb_eat && p->info->nb_eat != -1)
			return (NULL);
		ft_sleep(p);
	}
	return (NULL);
}

int		launch_routine(t_global *g, t_infos_philo *inf, int i)
{
	struct timeval	tv;

	g->sem = sem_open("global", 1);
	g->forks = sem_open("fork", O_CREAT, 432, inf->nb_philo);
	g->philos = malloc_lst(sizeof(t_philos *) * (inf->nb_philo + 1), g);
	if (!g->philos || !ft_fill_threads(g) || !g->sem || !g->forks)
		return (0);
	while (++i < inf->nb_philo)
	{
		gettimeofday(&tv, NULL);
		g->start_usec = tv.tv_usec;
		g->start_sec = tv.tv_sec;
		g->philos[i] = ft_init_philos(g, i);
		if (!g->philos)
			return (0);
		g->philos[i]->sem = sem_open("philo", 0);
		if (!g->philos[i]->sem)
			return (0);
		pthread_create(&g->philos[i]->thread, NULL, main_loop,
			(void *)g->philos[i]);
		pthread_detach(g->philos[i]->thread);
		pthread_join(g->philos[i]->thread, NULL);
		usleep(200);
	}
	return (1);
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
				sem_wait(global->sem);
				printf("\e[33m%.f \e[96m%d \033[0;31mdied\e[39m\n", ft_time_g(global, 1), i + 1);
				quit_program(global);
				return (ft_lstmalloc_clear(&global->lst_free, free));
			}
			if (eat == info->nb_philo)
			{
				sem_wait(global->sem);
				quit_program(global);
				return (ft_lstmalloc_clear(&global->lst_free, free));
			}
		}
	}
}

int main(int argc, char **argv)
{
	t_infos_philo	*info;
	t_global		*global;

	sem_unlink("global");
	sem_unlink("philo");
	sem_unlink("fork");
	global = malloc(sizeof(t_global));
	global->lst_free = NULL;
	add_lst_to_free(global, global);
	info = malloc_lst(sizeof(t_infos_philo), global);
	if (argc > 6 || argc <= 4)
	{
		printf("\e[33mError : Invalid number/value of parameters.\e[0m\n");
		return (ft_lstmalloc_clear(&global->lst_free, free));
	}
	if (!ft_init_infos_philo(info, global, argv, argc))
		return (ft_lstmalloc_clear(&global->lst_free, free));
	if (!launch_routine(global, info, -1))
		return (error_malloc(global, 1));
	loop_until_end_or_dead(global, info);
}
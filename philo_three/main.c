/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:39:20 by thallard          #+#    #+#             */
/*   Updated: 2021/03/26 15:24:27 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_one.h"

int		quit(t_global *g)
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

void	*alive_or_finish_eat(void *ptr)
{
	t_philos *p;

	p = ptr;
	while (1)
		if (p->tdie < ft_time_p(p, 1))
			exit(1);
		else if (p->times_eat >= p->info->nb_eat)
			break ;
	return (NULL);
}

void	*main_loop(t_philos **p)
{
	pthread_create(&(*p)->thread, NULL, alive_or_finish_eat, (*p));
	pthread_detach((*p)->thread);
	pthread_join((*p)->thread, NULL);
	while (1)
	{
		ft_think(*p);
		ft_take_forks(*p);
		if ((*p)->times_eat >= (*p)->info->nb_eat && (*p)->info->nb_eat != -1)
			break ;
		ft_sleep(*p);
	}
	exit(0);
	return (NULL);
}

int		launch_routine(t_global *g, t_infos_philo *inf, int i)
{
	struct timeval	tv;

	g->sem = sem_open("global", 1);
	g->forks = sem_open("fork", O_CREAT, 0660, inf->nb_philo);
	g->fork = malloc(inf->nb_philo * sizeof(pid_t));
	g->philos = malloc_lst(sizeof(t_philos *) * (inf->nb_philo + 1), g);
	if (!g->philos || !ft_fill_threads(g) || !g->sem || !g->forks)
		return (0);
	while (++i < inf->nb_philo)
	{
		gettimeofday(&tv, NULL);
		g->start_usec = tv.tv_usec;
		g->start_sec = tv.tv_sec;
		g->philos[i] = ft_init_philos(g, i);
		if (!g->philos[i])
			return (0);
		g->philos[i]->sem = sem_open("philo", 0);
		if (!g->philos[i]->sem)
			return (0);
		g->fork[i] = fork();
		if (!g->fork[i])
			main_loop(&g->philos[i]);
	}
	return (1);
}

int	wait_forks(t_global *g, t_infos_philo *info)
{
	int		i;
	int		return_value;
	pid_t	tmp;

	i = -1;
	while (++i < info->nb_philo)
	{
		return_value = 0;
		tmp = -1;
		while (!return_value && tmp <= 0)
			tmp = waitpid(-1, &return_value, 0);
		if (WEXITSTATUS(return_value))
			break ;
	}
	if (WEXITSTATUS(return_value))
	{
		i = -1;
		while (++i < info->nb_philo)
			if (tmp != g->fork[i])
				kill(g->fork[i], SIGKILL);
			else
				printf("\e[33m%.f \e[96m%d \033[31mdied\e[39m\n", \
					ft_time_g(g, 1), i + 1);
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_infos_philo	*info;
	t_global		*g;

	sem_unlink("global");
	sem_unlink("philo");
	sem_unlink("fork");
	g = malloc(sizeof(t_global));
	if (!g)
		return (error_malloc(NULL, 0));
			g->lst_free = NULL;
	info = malloc_lst(sizeof(t_infos_philo), g);
	if (!info)
		return (error_malloc(g, 1));
	if (argc > 6 || argc <= 4 )
	{
		printf("\e[33mError : Invalid number of parameters.\e[0m\n");
		return (ft_lstmalloc_clear(&g->lst_free, free, g));
	}
	if (!ft_init_infos_philo(info, g, argv, argc))
		return (quit(g) + ft_lstmalloc_clear(&g->lst_free, free, g));
	if (!launch_routine(g, info, -1))
		return (quit(g) + ft_lstmalloc_clear(&g->lst_free, free, g));
	wait_forks(g, info);
	return (1);
}


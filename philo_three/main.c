/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:39:20 by thallard          #+#    #+#             */
/*   Updated: 2021/03/25 23:13:37 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_one.h"

// void	stopping(t_global *g)
// {
// 	int		i;

// 	i = -1;
// 	sem_close(g->sem);
// 	while (++i < g->info->nb_philo)
// 	{
// 		pthread_detach(g->philos[i]->thread);
// 		sem_close(g->philos[i]->sem);
		
// 	}
// 	sem_unlink("global");
// 	sem_unlink("philo");
// 	sem_unlink("fork");
// }

void	*alive(void *ptr)
{
	t_philos *p;

	p = ptr;
	while (1)
		if (p->tdie < ft_time_p(p, 1))
		{	
			dprintf(1, "\e[31mmort %ld\n", p->pos + 1);
			exit(1);
		}
			
	return (NULL);
}

void	*main_loop(t_philos **p)
{
	pthread_create(&(*p)->thread, NULL, alive, (*p));
	pthread_detach((*p)->thread);
	pthread_join((*p)->thread, NULL);
	while (1)
	{
		// if ((*p)->tdie < ft_time_p(*p, 1))
		// 	break ;
		ft_take_forks(*p);
		if ((*p)->times_eat >= (*p)->info->nb_eat && (*p)->info->nb_eat != -1)
			break ;
		ft_sleep(*p);
		
		ft_think(*p);
		
	}
	exit(0);
	return (NULL);
}

void		launch_routine(t_global *g, t_infos_philo *inf)
{
	int				i;
	struct timeval	tv;

	i = -1;
	g->sem = sem_open("global", 1);
	ft_fill_threads(g);
	// pthread_mutex_init(&g->mutex, NULL);
	// g->forks = ft_fill_mutex(g);
	g->forks = sem_open("fork", O_CREAT, 0660, inf->nb_philo);
	g->fork = malloc(inf->nb_philo * sizeof(pid_t));
            
	g->philos = malloc_lst(sizeof(t_philos *) * (inf->nb_philo + 1), g);
	while (++i < inf->nb_philo)
	{
		gettimeofday(&tv, NULL);
		g->start_usec = tv.tv_usec;
		g->start_sec = tv.tv_sec;
		
		g->philos[i] = ft_init_philos(g, i);
			g->philos[i]->sem = sem_open("philo", 0);
	
		// pthread_mutex_init(&(g->philos[i]->mutex), NULL);
		// pthread_create(&g->philos[i]->thread, NULL, main_loop, (void *)g->philos[i]);
		// pthread_detach(g->philos[i]->thread);
		// pthread_join(g->philos[i]->thread, NULL);
		g->fork[i] = fork();
		
		if (!g->fork[i])
			main_loop(&g->philos[i]);
		
	}
}

int loop_until_end_or_dead(t_global *g, t_infos_philo *info)
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
				printf("\e[33m%.f \e[96m%d \033[0;31mdied\e[39m\n", ft_time_g(g, 1), i + 1);
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_infos_philo *info;
	t_global *global;

	sem_unlink("global");
	sem_unlink("philo");
	sem_unlink("fork");
	global = malloc(sizeof(t_global));
	global->lst_free = NULL;
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
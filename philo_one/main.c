/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:39:20 by thallard          #+#    #+#             */
/*   Updated: 2021/03/22 17:31:10 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_one.h"



int wait_threads(t_global *global)
{
	int loop;
	int i;

	loop = 1;
	while (loop)
	{
		loop = 0;
		i = -1;
		while (++i < global->info->nb_philo)
		{
			// dprintf(1, "debug du join = %d\n", i);
			if (!global->philos[i]->alive)
			{
				dprintf(1, "mort\n");
				return (0);
			}

			if (pthread_join(global->philos[i]->thread, NULL))
			{

				loop = 1;
			}
		}
	}

	return (1);
}

int check_eats(t_global *g)
{
	int		j;

	j = -1;
	while (++j < g->info->nb_philo)
	{
		// pthread_mutex_lock(&g->safe[j]);
		if (g->philos[j]->times_eat != g->info->nb_eat)
		{
		//	dprintf(1, "debug %d et %ld\n", j, g->philos[j]->times_eat);
			// pthread_mutex_unlock(&g->safe[j]);
			return (0);
		}
			// pthread_mutex_unlock(&g->safe[j]);
	}
		
	dprintf(1, "fin normale\n");
	return (1);
}

int are_alive(t_philos *p)
{
	int i;

	i = -1;
	while (++i < p->info->nb_philo)
	{
		if (!p->philos[i]->alive)
			return (0);
	}
	return (1);
}

void	*main_loop(void *ptr)
{
	t_philos	*p;

	p = ptr;
	while (1)
	{
		if (p->tdie <= ft_time_p(p, 1))
		{
			p->alive = 0;
			return (NULL);
		}
		ft_take_forks(p);
		if (p->times_eat >= p->info->nb_eat && p->info->nb_eat != -1)
			return (NULL);
		ft_sleep(p);
		ft_think(p);
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	t_infos_philo *info;
	t_global *global;
	struct timeval tv;
	dprintf(1, "%d\n", argc);
	global = malloc(sizeof(t_global));
	info = malloc(sizeof(t_infos_philo));
	global->lst_free = NULL;
	gettimeofday(&tv, NULL);
	global->start_usec = tv.tv_usec;
	global->start_sec = tv.tv_sec;
	if (argc > 6 || argc <= 4)
	{
		printf("erreur de parametres\n");
		return (0);
	}
	if (!ft_init_infos_philo(info, global, argv, argc))
	return (0);
	ft_fill_threads(global);
	global->forks = ft_fill_mutex(global);
	global->lock = ft_fill_mutex(global);
	global->safe = ft_fill_mutex(global);
	global->philos = malloc_lst(sizeof(t_philos *) * (info->nb_philo + 1), global);
	int		i;

	i = -1;
	while (++i < info->nb_philo)
	{
		global->philos[i] = ft_init_philos(global, i);
		global->i = i;
		pthread_create(&global->philos[i]->thread, NULL, main_loop, (void *)global->philos[i]);
		pthread_detach(global->philos[i]->thread);
		pthread_join(global->philos[i]->thread, NULL);
	}
	i = -1;
	int loop = 1;
	while (loop)
	{
		i = -1;
		while (++i < info->nb_philo)
		{
			if (check_eats(global))
			{
				dprintf(1, "ils ont fini d emanger, fin du pgraomme\n");
				return (0);
			}
			
			if (!global->philos[i]->alive || global->philos[i]->tdie <= ft_time_g(global, 1))
			{
				printf("\e[33m%.f \e[96m%d \033[0;31mdieded\e[39m\n", ft_time_g(global, 1), i + 1);
				
				return (0);
			}
			
		}
	}
	// wait_threads(global);
	dprintf(1, "[%ld] [%ld] [%ld] [%ld] [%ld]\n", global->info->nb_philo, info->time_die, info->time_eat, info->time_sleep, info->nb_eat);
}
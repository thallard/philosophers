/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:39:20 by thallard          #+#    #+#             */
/*   Updated: 2021/03/18 16:07:51 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"


pthread_mutex_t		ft_create_fork(t_global *g)
{
	pthread_mutex_t mutex;

	if (pthread_mutex_init(&mutex, NULL))
		ft_exit(g);
	return (mutex);
}

int		ft_fill_forks(t_global *g)
{
	int		i;

	i = -1;
	if (!(g->forks = malloc_lst(sizeof(pthread_mutex_t) * (g->info->nb_philo + 1), g)))
		ft_exit(g);
	while (++i < g->info->nb_philo)
		g->forks[i] = ft_create_fork(g);
	// dprintf(1, "res de i et total = %d %ld\n", i, g->info->nb_philo);
	return (0);
}

pthread_mutex_t	*ft_fill_mutex(t_global *g)
{
	int		i;
	pthread_mutex_t	*forks;
	i = -1;
	if (!(forks = malloc_lst(sizeof(pthread_mutex_t) * (g->info->nb_philo + 1), g)))
		ft_exit(g);
	while (++i < g->info->nb_philo)
		forks[i] = ft_create_fork(g);
	// dprintf(1, "res de i et total = %d %ld\n", i, g->info->nb_philo);
	return (forks);
}

pthread_t	ft_create_thread(t_global *global)
{
	pthread_t	thread;

	if (!(thread = malloc_lst(sizeof(pthread_t), global)))
		ft_exit(global);
	return (thread);
}

int			ft_fill_threads(t_global *global)
{
	int		i;

	i = -1;
	if (!(global->threads = malloc_lst(sizeof(pthread_t) * (global->info->nb_philo + 2000), global)))
		ft_exit(global);
	while (++i < global->info->nb_philo)
	{
		// dprintf(1, "dbeug de i = %d\n", i);
			global->threads[i] = ft_create_thread(global);
	}
	
	global->threads[i] = NULL;
	return (1);
}

void		ft_init_infos_philo(t_infos_philo *info, t_global *g, char **argv)
{
	info->nb_philo = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	info->nb_eat = ft_atoi(argv[5]);
	g->i = 0;
	g->info = info;
}


t_philos	*ft_init_philos(t_global *g, int pos)
{
	t_philos	*p;

	p = malloc_lst(sizeof(t_philos), g);
	p->forks = g->forks;
	p->pos = pos + 1;
	p->thread = ft_create_thread(g);
	p->times_eat = 0;
	p->tsleep = 0;
	p->tthink = 0;
	p->tdie = ft_time(g, 1) + g->info->time_die;
	p->teat = 0;
	p->start_sec = g->start_sec;
	p->start_usec = g->start_usec;
	return (p);
}

int		check_eats(t_global *g)
{
	int		j;

	j = -1;
	while (++j < g->info->nb_philo)
	{
		dprintf(1, "debug de la bouffe de %d a manger %ld\n", j, g->philos[j]->times_eat);
			if (g->philos[j]->times_eat != g->info->nb_eat)
			return (0);
	}
	dprintf(1, "fin normale\n\n\n");
			
	return (1);
}

int		ft_take_forks(t_global *g, int pos, t_philos *p)
{
	int		forks = 0;

	(void)pos;
	forks = g->i;

	pthread_mutex_lock(&g->forks[p->pos]);
	pthread_mutex_lock(&g->forks[(p->pos % g->info->nb_philo) + 1]);
	printf("\e[33m%.f \e[96m%ld \e[32mhas taken a fork %ld\e[39m\n", ft_time(g, 1), p->pos, p->pos);
	printf("\e[33m%.f \e[96m%ld \e[32mhas taken a fork %ld\e[39m\n", ft_time(g, 1), p->pos, ((p->pos) % g->info->nb_philo) + 1);
	printf("\e[33m%.f \e[96m%ld \e[33mis eating\e[39m\n", ft_time(g, 1), p->pos);
	p->tdie = ft_time(g, 1) + g->info->time_die;
	usleep(g->info->time_eat * 1000);
	p->times_eat++;
	pthread_mutex_unlock(&g->forks[(p->pos % g->info->nb_philo) + 1]);
	pthread_mutex_unlock(&g->forks[p->pos]);



	// }
	// dprintf("oui\n");
	return (forks);
}

void	ft_sleep(t_global *g, t_philos *p)
{
	usleep(g->info->time_sleep * 1000);
	printf("\e[33m%.f \e[96m%ld is sleeping\e[39m\n", ft_time(g, 1), p->pos);
}


void	*function_thread(void *ptr)
{
	t_global	*g;
	t_philos	*p;

	g = ptr;
	p = g->philos[g->i];
	int		i;

	i = -1;
	dprintf(1, "%d\n",g->i);
	while (p->times_eat < g->info->nb_eat)
	{
		if (p->tdie <= ft_time(g, 1))
		{
			printf("\e[33m%.f \e[96m%ld \033[0;31mdied\e[39m\n", ft_time(g, 1), p->pos);
			return (NULL);
		}
			dprintf(1, "debug miam miam %ld %ld\n", p->times_eat, g->info->nb_eat);
		ft_take_forks(g, g->i, p);
		if (p->times_eat >= g->info->nb_eat)
			return (NULL);
		ft_sleep(g, p);
		
	}
	dprintf(1, "fin du programme %ld et la bouffe %ld\n", p->pos, p->times_eat);
	return (NULL);
}

int		main(int argc, char **argv)
{
	t_infos_philo	*info;
	t_global		*global;
	struct timeval	tv;

	global = malloc(sizeof(t_global));
	info = malloc(sizeof(t_infos_philo));
	global->lst_free = NULL;
	gettimeofday(&tv, NULL);
	global->start_usec = tv.tv_usec;
	global->start_sec = tv.tv_sec;
	if (argc > 6 || argc <= 5)
	{
		printf("erreur de parametres\n");
		return (0);
	}
	ft_init_infos_philo(info, global, argv);
	ft_fill_threads(global);
	global->forks = ft_fill_mutex(global);
	global->lock = ft_fill_mutex(global);
	int		i;
	global->philos = malloc_lst(sizeof(t_philos *) * (info->nb_philo + 1), global);
	i = -1;
	while (++i < info->nb_philo)
	{
		global->philos[i] = ft_init_philos(global, i);
		global->i = i;
		pthread_create(&global->philos[i]->thread, NULL, function_thread, (void*)global);
	}
	i = -1;
		int		loop = 1;
	while (loop)
	{
		i = -1;
		while (++i < info->nb_philo)
		{
		
			// dprintf(1, "debug = %d\n", check_eats(global));
			if (check_eats(global))
			{
				dprintf(1, "ils ont fini d emanger, fin du pgraomme\n");
					return (0);
			}
			if (global->philos[i]->tdie <= ft_time(global, 1))
			{
				dprintf(1, "\e[33m%.f died %d\n", ft_time(global, 1), i + 1);
					return (0);
			}
			
		
			
		}
	}
	while (loop)
	{
		loop = 0;
		i = -1;
		while (++i < global->info->nb_philo)
		{
			// dprintf(1, "debug du join = %d\n", i);
				if (pthread_join(global->philos[i]->thread, NULL))
					loop = 1;
			
				
		}
	}
	dprintf(1, "[%ld] [%ld] [%ld] [%ld] [%ld]\n", global->info->nb_philo, info->time_die, info->time_eat, info->time_sleep, info->nb_eat);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:03:45 by thallard          #+#    #+#             */
/*   Updated: 2021/03/03 11:52:22 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

// static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

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
	if (!(global->threads = malloc_lst(sizeof(pthread_t) *
		(global->info->nb_philo + 2), global)))
		ft_exit(global);
	while (++i < global->info->nb_philo)
	{
		// dprintf(1, "dbeug de i = %d\n", i);
			global->threads[i] = ft_create_thread(global);
	}
	
	// global->threads[i] = NULL;
	return (1);
}

int		ft_take_forks(t_global *g, int pos, t_philos *p)
{
	int		forks = 0;

	forks = g->i;
	dprintf(1, "Debug entree %d\n", forks);
	pthread_mutex_lock(&g->lock[pos]);
	pthread_mutex_lock(&g->forks[pos]);
	pthread_mutex_lock(&g->forks[g->info->nb_philo % (pos + 1)]);
	printf("\e[33m%.f \e[96m%d \e[32mhas taken a fork %d\e[39m\n", ft_time(g, 1), g->i, pos);
	printf("\e[33m%.f \e[96m%d \e[32mhas taken a fork %ld\e[39m\n", ft_time(g, 1), g->i, (pos + 1) % g->info->nb_philo);
	printf("\e[33m%.f \e[96m%d \e[33mis eating\e[39m\n", ft_time(g, 1), g->i);
	usleep(g->info->time_eat);
		p->times_eat++;
	pthread_mutex_unlock(&g->forks[pos]);
	pthread_mutex_unlock(&g->forks[g->info->nb_philo % (pos + 1)]);
	pthread_mutex_unlock(&g->lock[pos]);

	// }
	// dprintf("oui\n");
	return (forks);
}

void	*function_thread(void *arg)
{
	t_global *g;
	t_philos *p;
	// struct timeval tv;
	// struct timezone tz;

	// int forks = 0;
	g = arg;
	p = g->philos[g->i];//g->philos[g->i];

	fprintf(stderr, "=> %d\n", p->times_eat);
	while (p->times_eat < g->info->time_eat)
	{
		// dprintf(1, "Fin du %ld\n", g->i);
		
		ft_take_forks(g, g->i, p);
		dprintf(1, "debug miam miam %d\n", p->times_eat);
	// 	gettimeofday(&tv, &tz);
		// if (ft_time(g, 0) + g->info->time_die >= p->tdie)
		// {
		// 	dprintf(1, "\e[33m%.f \e[96m%ld \e[32mdied\e[39m\n", ft_time(g,1 ), g->i);
		// 	ft_fin(g, g->i);
		// }
		
	// 	// dprintf(1, "debug start et time die = %d %ld\n", g->start, g->info->time_die);
	// 	if (tv.tv_usec >= g->start + g->info->time_die)
	// 	{
	// 		gettimeofday(&tv, &tz);
	// 		dprintf(1, "\e[33m%d \e[96m%ld \e[32mdied\e[39m\n", tv.tv_usec - g->start, g->i);
	// 		ft_fin(g, g->i);
	// 		break ;
	// 	}
	// 	// if (forks == 2)
	// 	// {
			
	// 	// 	usleep(g->info->time_eat);
	// 	// 	gettimeofday(&tv, &tz);
	// 	// 	fprintf(stderr, "\e[33m%d \e[96m%ld \e[32mfin\e[39m\n", tv.tv_usec - g->start, g->i);
			// break;
	// 	// }
	
	 }
	 
	return NULL;
}

int			main(int argc, char **argv)
{
	t_infos_philo	info;
	t_global		global;

	struct timeval tv;
	gettimeofday(&tv, NULL);
	global.start_usec = tv.tv_usec;
	global.start_sec = tv.tv_sec;
	// dprintf(1, "dbeug de argc = %d\n", argc);
	if (argc > 6 || argc <= 5)
	{
		printf("erreur de parametres\n");
		return (0);
	}
	ft_init_infos_philo(&info, &global, argv);
	ft_fill_threads(&global);
	// ft_fill_forks(global);
	
	global.forks = ft_fill_mutex(&global);
	global.lock = ft_fill_mutex(&global);
	global.i = 0;
	global.philos = malloc_lst(sizeof(t_philos *) * (global.info->nb_philo + 1), &global);
	global.philos[global.info->nb_philo] = NULL;

	int j = -1;
	while (++j < global.info->nb_philo)
	{
		// printf("FINI = %ld\n", global.i );
		global.philos[j] = ft_init_philos(&global, j);
		// printf("FINI = %ld\n", global.i );
		// dprintf(1, "Je lance le thread = %d\n", j);
		global.i = j;
		pthread_create(&global.philos[j]->thread, NULL, function_thread, &global);
		
		// pthread_detach(global.philos[j]->thread);
		pthread_join(global.philos[j]->thread, NULL);
		// global.i++;
	}

 		
	// sleep(1);
	// int		loop = 1;
	// int		i;
	// while (loop)
	// {
	// 	loop = 0;
	// 	i = 1;
	// 	while (i < global.info->nb_philo)
	// 	{
	// 		dprintf(1, "debug du join = %d\n", i);
	// 			if (pthread_join(*global.philos[i]->thread, NULL))
	// 				loop = 1;
	// 		i++;
				
	// 	}
	// }
	// printf("FINI\n");
	//  gettimeofday (&e, NULL);
 
    // printf("Simulation finie : %ld ms\n", ((e.tv_sec - s.tv_sec) * 1000000 + e.tv_usec) - s.tv_usec);
	dprintf(1, "[%ld] [%ld] [%ld] [%ld] [%ld]\n", global.info->nb_philo, info.time_die, info.time_eat, info.time_sleep, info.nb_eat);
}
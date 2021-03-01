/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:03:45 by thallard          #+#    #+#             */
/*   Updated: 2021/03/01 15:21:54 by thallard         ###   ########lyon.fr   */
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

pthread_t	*ft_create_thread(t_global *global)
{
	pthread_t	*thread;

	if (!(thread = malloc_lst(sizeof(pthread_t), global)))
		ft_exit(global);
	return (thread);
}

int			ft_fill_threads(t_global *global)
{
	int		i;

	i = 0;
	if (!(global->threads = malloc_lst(sizeof(pthread_t *) *
		(global->info->nb_philo + 2), global)))
		ft_exit(global);
	while (++i <= global->info->nb_philo)
	{
		// dprintf(1, "dbeug de i = %d\n", i);
			global->threads[i] = ft_create_thread(global);
	}
	
	global->threads[i] = NULL;
	return (1);
}

int		ft_take_forks(t_global *g, int pos, t_philos *p)
{
	int		forks = 0;
	// struct timeval tv;
	// struct timezone tz;

	

	forks = g->i;
	dprintf(1, "Debug entree %d\n", forks);
	// if (pos - 1 <= 0)
	// {
	// 	pthread_mutex_lock(&g->forks[pos]);
	// 	pthread_mutex_lock(&g->forks[g->info->nb_philo]);
	// 	dprintf(1, "Je lock les fourchette a la position : %d et %ld pour le Philosophe : %d\n", pos, g->info->nb_philo, pos);
	// 	dprintf(1, "\e[33m%.f \e[96m%ld \e[32mhas taken a fork\e[39m\n", ft_time(g, 1), g->i);
	// 	dprintf(1, "\e[33m%.f \e[96m%ld \e[32mhas taken a fork\e[39m\n", ft_time(g, 1), g->i);
	// 	dprintf(1,"\e[33m%.f \e[96m%ld \e[32mis eating\e[39m\n", ft_time(g, 1), g->i);
	// 	usleep(g->info->time_eat);
	// 	pthread_mutex_unlock(&g->forks[pos]);
	// 	pthread_mutex_unlock(&g->forks[g->info->nb_philo]);
	// }
	// else
	// {
	pthread_mutex_lock(&g->lock[pos]);
	if (p->times_eat < g->info->nb_eat)
	{
		// dprintf(1, "debug de pos + 1 = %ld %d %ld et times_eat %d\n",(pos + 1) % g->info->nb_philo, pos + 1, g->info->nb_philo, p->times_eat);
		pthread_mutex_lock(&g->forks[pos]);
		pthread_mutex_lock(&g->forks[(pos + 1) % g->info->nb_philo]);
			// dprintf(1, "delock les mutex\n");
		// dprintf(1, "Je lock les fourchette a la position : %d et %ld pour le Philosophe : %d\n", pos, (pos + 1) % g->info->nb_philo, pos);
		dprintf(1, "\e[33m%.f \e[96m%d \e[32mhas taken a fork %d\e[39m\n", ft_time(g, 1), g->i, pos);
		dprintf(1, "\e[33m%.f \e[96m%d \e[32mhas taken a fork %ld\e[39m\n", ft_time(g, 1), g->i, (pos + 1) % g->info->nb_philo);
		dprintf(1,"\e[33m%.f \e[96m%d \e[33mis eating\e[39m\n", ft_time(g, 1), g->i);
		usleep(g->info->time_eat);
			p->times_eat++;
		pthread_mutex_unlock(&g->forks[pos]);
		pthread_mutex_unlock(&g->forks[(pos + 1) % g->info->nb_philo]);
	}
	pthread_mutex_unlock(&g->lock[pos]);
	// }
	// dprintf(1, "oui\n");
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
	p = g->philos[g->i];
	fprintf(stderr, "%d\n", g->i);
	while (p->times_eat < g->info->nb_eat)
	{
		// dprintf(1, "Fin du %ld\n", g->i);
		
			ft_take_forks(g, g->i, p);
		// dprintf(1, "debug miam miam %d\n", p->times_eat);
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
	// 	// 	break;
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
	global.lock =ft_fill_mutex(&global);
	global.i = 1;
	global.philos = malloc_lst(sizeof(t_philos) * (global.info->nb_philo + 2), &global);
	
	while (global.i < global.info->nb_philo)
	{
		// printf("FINI = %ld\n", global.i );
		global.philos[global.i] = ft_init_philos(&global, global.i);
		// printf("FINI = %ld\n", global.i );
		pthread_create(global.philos[global.i]->thread, NULL, function_thread, &global);
		usleep(5000);
		// pthread_detach(*global.philos[global.i]->thread);
		// pthread_join(*global.philos[global.i]->thread, NULL);
		global.i += 1;
	}

 		
	sleep(1);
	int		loop = 1;
	int		i;
	while (loop)
	{
		loop = 0;
		i = 0;
		while (++i < global.info->nb_philo)
		{
			dprintf(1, "debug du join = %d\n", i);
				if (pthread_join(*global.philos[i]->thread, NULL))
					loop = 1;
				
		}
	}
	// printf("FINI\n");
	//  gettimeofday (&e, NULL);
 
    // printf("Simulation finie : %ld ms\n", ((e.tv_sec - s.tv_sec) * 1000000 + e.tv_usec) - s.tv_usec);
	dprintf(1, "[%ld] [%ld] [%ld] [%ld] [%ld]\n", global.info->nb_philo, info.time_die, info.time_eat, info.time_sleep, info.nb_eat);
}
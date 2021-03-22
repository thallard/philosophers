/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:39:20 by thallard          #+#    #+#             */
/*   Updated: 2021/03/22 13:49:26 by thallard         ###   ########lyon.fr   */
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
void ft_init_infos_philo(t_infos_philo *info, t_global *g, char **argv)
{
	info->nb_philo = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	info->nb_eat = ft_atoi(argv[5]);
	g->i = 0;
	g->info = info;
}

t_philos *ft_init_philos(t_global *g, int pos)
{
	t_philos *p;

	p = malloc_lst(sizeof(t_philos), g);
	p->forks = g->forks;
	p->locks = g->lock;
	p->info = g->info;
	p->safe = g->safe;
	p->pos = pos + 1;
	p->philos = g->philos;
	p->thread = ft_create_thread(g);
	p->times_eat = 0;
	p->tsleep = 0;
	p->tthink = 0;
	p->alive = 1;
	p->tdie = ft_time_g(g, 1) + g->info->time_die;
	p->teat = 0;
	p->start_sec = g->start_sec;
	p->start_usec = g->start_usec;
	return (p);
}

int check_eats(t_global *g)
{
	int j;

	j = -1;
	while (++j < g->info->nb_philo)
	{
		// dprintf(1, "debug de la bouffe de %d a manger %ld\n", j, g->philos[j]->times_eat);
		if (g->philos[j]->times_eat != g->info->nb_eat)
			return (0);
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

int ft_take_forks(t_philos *p)
{

	pthread_mutex_lock(&p->locks[p->pos - 1]);
	pthread_mutex_lock(&p->forks[p->pos - 1]);
	pthread_mutex_lock(&p->forks[((p->pos - 1) % p->info->nb_philo) + 1]);
	printf("\e[33m%.f \e[96m%ld \e[32mhas taken a fork %ld\e[39m\n", ft_time_p(p, 1), p->pos, p->pos);
	printf("\e[33m%.f \e[96m%ld \e[32mhas taken a fork %ld\e[39m\n", ft_time_p(p, 1), p->pos, ((p->pos) % p->info->nb_philo) + 1);
	printf("\e[33m%.f \e[96m%ld \e[33mis eating\e[39m\n", ft_time_p(p, 1), p->pos);
	p->tdie = ft_time_p(p, 1) + p->info->time_die;
	usleep(p->info->time_eat * 1000);
	p->times_eat++;
	pthread_mutex_unlock(&p->forks[((p->pos - 1) % p->info->nb_philo) + 1]);
	pthread_mutex_unlock(&p->forks[p->pos - 1]);
	pthread_mutex_unlock(&p->locks[p->pos - 1]);

	return (0);
}

void ft_sleep(t_philos *p)
{
	printf("\e[33m%.f \e[96m%ld is sleeping\e[39m\n", ft_time_p(p, 1), p->pos);
	pthread_mutex_lock(&p->locks[p->pos - 1]);
	usleep(p->info->time_sleep * 1000);
	pthread_mutex_unlock(&p->locks[p->pos - 1]);
}

void ft_think(t_philos *p)
{
	pthread_mutex_lock(&p->safe[p->pos - 1]);
	printf("\e[33m%.f \e[96m%ld \e[0;35mis thinking\e[39m\n", ft_time_p(p, 1), p->pos);
	pthread_mutex_unlock(&p->safe[p->pos - 1]);
}

void *function_thread(void *ptr)
{
	t_philos	*p;

	p = ptr;
	while (p->times_eat < p->info->nb_eat && p->times_eat != -1)
	{
		if (p->tdie <= ft_time_p(p, 1))
		{
			p->alive = 0;
			return (NULL);
		}
		ft_take_forks(p);
		if (p->times_eat >= p->info->nb_eat)
			return (NULL);
		ft_sleep(p);
		ft_think(p);
	}	return (NULL);
}

int main(int argc, char **argv)
{
	t_infos_philo *info;
	t_global *global;
	struct timeval tv;

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
	global->safe = ft_fill_mutex(global);
	global->philos = malloc_lst(sizeof(t_philos *) * (info->nb_philo + 1), global);
	int		i;

	i = -1;
	while (++i < info->nb_philo)
	{
		global->philos[i] = ft_init_philos(global, i);
		pthread_create(&global->philos[i]->thread, NULL, function_thread, (void *)global->philos[i]);
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

			if (global->philos[i]->tdie <= ft_time_g(global, 1))
			{
				dprintf(1, "\e[33m%.f \e[96m%d \033[0;31mdied\e[39m\n", ft_time_g(global, 1), i + 1);
				//printf("\e[33m%.f \e[96m%ld \033[0;31mdied\e[39m\n", ft_time_p(p, 1), p->pos);
				return (0);
			}
		}
	}
	wait_threads(global);

	dprintf(1, "[%ld] [%ld] [%ld] [%ld] [%ld]\n", global->info->nb_philo, info->time_die, info->time_eat, info->time_sleep, info->nb_eat);
}
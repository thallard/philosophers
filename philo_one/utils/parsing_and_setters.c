/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_and_setters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:06:48 by thallard          #+#    #+#             */
/*   Updated: 2021/03/22 14:40:43 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

int	ft_init_infos_philo(t_infos_philo *info, t_global *g, char **argv, int argc)
{
	info->nb_philo = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	if (info->nb_philo < 0 || info->time_die < 0 || info->time_eat < 0
		|| info->time_sleep < 0)
	{
		printf("\e[0;31mError : A value is negative.\e[0m\n");
		return (0);
	}
	if (argc == 6)
		info->nb_eat = ft_atoi(argv[5]);
	else
		info->nb_eat = -1;
	dprintf(1, "%ld\n", info->nb_eat);
	g->i = 0;
	g->info = info;
	return (1);
}

t_philos	*ft_init_philos(t_global *g, int pos)
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


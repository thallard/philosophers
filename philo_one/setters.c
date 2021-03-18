/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:52:58 by thallard          #+#    #+#             */
/*   Updated: 2021/03/03 11:06:09 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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


	// p = g->philos[pos];
	p = malloc_lst(sizeof(t_philos), g);
	p->pos = pos;
	p->thread = ft_create_thread(g);
	p->times_eat = 0;
	p->tsleep = 0;
	p->tthink = 0;
	p->tdie = ft_time(g, 0) + g->info->time_die;
	p->teat = 0;
	p->start_sec = g->start_sec;
	p->start_usec = g->start_usec;
	return (p);
}
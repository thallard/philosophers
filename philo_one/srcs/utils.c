/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:06:48 by thallard          #+#    #+#             */
/*   Updated: 2021/03/25 23:43:05 by thallard         ###   ########lyon.fr   */
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
	g->info = info;
	return (1);
}

t_philos	*ft_init_philos(t_global *g, int pos)
{
	t_philos *p;

	p = malloc_lst(sizeof(t_philos), g);
	p->forks = g->forks;
	p->info = g->info;
	p->pos = pos;
	p->thread = ft_create_thread(g);
	p->times_eat = 0;
	p->tdie = ft_time_g(g, 1) + g->info->time_die;
	p->start_sec = g->start_sec;
	p->start_usec = g->start_usec;
	return (p);
}

double	ft_time_g(t_global *g, int boolstart)
{
	struct timeval end;

	gettimeofday (&end, NULL);
	if (boolstart)
		return ((double)(end.tv_usec - g->start_usec) / 1000 + (double) (end.tv_sec - g->start_sec) * 1000);
	return (end.tv_usec);
}

double	ft_time_p(t_philos *p, int boolstart)
{
		struct timeval end;

	gettimeofday (&end, NULL);
	if (boolstart)
		return ((double)(end.tv_usec - p->start_usec) / 1000 + (double) (end.tv_sec - p->start_sec) * 1000);
	return (end.tv_usec);
}

int	error_malloc(t_global *g, int freeall)
{
	if (freeall)
		ft_lstmalloc_clear(&g->lst_free, free);
	printf("\e[31mError : A malloc has failed.\e[0m\n");
	return (0);
}
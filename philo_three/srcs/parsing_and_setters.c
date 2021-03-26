/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_and_setters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:06:48 by thallard          #+#    #+#             */
/*   Updated: 2021/03/26 17:24:33 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

int	is_d(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
	return (1);
}

int	ft_init_infos_philo(t_infos_philo *info, t_global *g, char **argv, int argc)
{
	if (!is_d(argv[1]) || !is_d(argv[2]) || !is_d(argv[3]) || !is_d(argv[4]) \
		 || (argc == 6 && !is_d(argv[5])))
	{
		printf("\e[0;31mError : Alphanumeric characters in parameters.\e[0m\n");
		return (0);
	}
	info->nb_philo = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	if (info->nb_philo < 2 || info->time_die <= 0 || info->time_eat <= 0
		|| info->time_sleep <= 0 || (argc == 6 && ft_atoi(argv[5]) <= 0))
	{
		printf("\e[0;31mError : A value is negative/incorrect.\e[0m\n");
		return (0);
	}
	if (argc == 6 && ft_atoi(argv[5]) >= 0)
		info->nb_eat = ft_atoi(argv[5]);
	else
		info->nb_eat = -1;
	g->info = info;
	return (1);
}

t_philos	*ft_init_philos(t_global *g, int pos)
{
	t_philos	*p;

	p = malloc_lst(sizeof(t_philos), g);
	p->forks = g->forks;
	p->info = g->info;
	p->pos = pos;
	p->global = g;
	p->thread = ft_create_thread(g);
	p->times_eat = 0;
	p->tdie = ft_time_g(g, 1) + g->info->time_die;
	p->start_sec = g->start_sec;
	p->start_usec = g->start_usec;
	return (p);
}

double	ft_time_g(t_global *g, int boolstart)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	if (boolstart)
		return ((double)(end.tv_usec - g->start_usec) / 1000 + \
		(double)(end.tv_sec - g->start_sec) *1000);
	return (end.tv_usec);
}

double	ft_time_p(t_philos *p, int boolstart)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	if (boolstart)
		return ((double)(end.tv_usec - p->start_usec) / 1000 + \
		(double)(end.tv_sec - p->start_sec) *1000);
	return (end.tv_usec);
}

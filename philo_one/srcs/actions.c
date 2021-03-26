/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:58:33 by thallard          #+#    #+#             */
/*   Updated: 2021/03/26 15:54:14 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

int	ft_take_forks(t_philos *p)
{
	pthread_mutex_lock(&p->forks[p->pos]);
	print_log(p, FORK);
	pthread_mutex_lock(&p->forks[((p->pos) % p->info->nb_philo) + 1]);
	print_log(p, FORK);
	print_log(p, EAT);
	p->tdie = 5 + ft_time_p(p, 1) + p->info->time_die;
	usleep(p->info->time_eat * 1000);
	p->times_eat++;
	pthread_mutex_unlock(&p->forks[((p->pos) % p->info->nb_philo) + 1]);
	pthread_mutex_unlock(&p->forks[p->pos]);
	return (0);
}

void	ft_sleep(t_philos *p)
{
	print_log(p, SLEEP);
	usleep(p->info->time_sleep * 1000);
}

void	ft_think(t_philos *p)
{
	print_log(p, THINK);
}

void	print_log(t_philos *p, int action)
{
	pthread_mutex_lock(&(p->mutex));
	if (action == 1)
		printf("\e[33m%.f \e[96m%ld \e[32mhas taken a fork\e[39m\n", \
		ft_time_p(p, 1), p->pos + 1);
	else if (action == 3)
		printf("\e[33m%.f \e[96m%ld \e[33mis eating\e[39m\n", \
		ft_time_p(p, 1), p->pos + 1);
	else if (action == 4)
		printf("\e[33m%.f \e[96m%ld is sleeping\e[39m\n", \
		ft_time_p(p, 1), p->pos + 1);
	else if (action == 5)
		printf("\e[33m%.f \e[96m%ld \e[0;35mis thinking\e[39m\n", \
		ft_time_p(p, 1), p->pos + 1);
	pthread_mutex_unlock(&(p->mutex));
}

int	error_malloc(t_global *g, int freeall)
{
	if (freeall)
		ft_lstmalloc_clear(&g->lst_free, free, g);
	printf("\e[31mError : A malloc has failed.\e[0m\n");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:58:33 by thallard          #+#    #+#             */
/*   Updated: 2021/03/22 13:59:33 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

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
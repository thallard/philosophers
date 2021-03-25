/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:58:33 by thallard          #+#    #+#             */
/*   Updated: 2021/03/25 22:57:38 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

int ft_take_forks(t_philos *p)
{
	sem_wait(p->global->forks);
	print_log(p, FORK);
	sem_wait(p->global->forks);
	print_log(p, FORK);
	p->times_eat++;
	print_log(p, EAT);
	p->tdie = ft_time_p(p, 1) + p->info->time_die + 30;
	usleep(p->info->time_eat * 1000);
	sem_post(p->global->forks);
	sem_post(p->global->forks);
	return (0);
}

void ft_sleep(t_philos *p)
{
	sem_wait(p->sem);
	print_log(p, SLEEP);
	usleep(p->info->time_sleep * 1000);
	sem_post(p->sem);
}

void ft_think(t_philos *p)
{
	print_log(p, THINK);
}

void print_log(t_philos *p, int action)
{
	if (action == 1)
		printf("\e[33m%.f \e[96m%ld \e[32mhas taken a fork\e[39m\n", ft_time_p(p, 1), p->pos + 1);
	else if (action == 3)
		printf("\e[33m%.f \e[96m%ld \e[33mis eating\e[39m\n", ft_time_p(p, 1), p->pos + 1);
	else if (action == 4)
		printf("\e[33m%.f \e[96m%ld is sleeping\e[39m\n", ft_time_p(p, 1), p->pos + 1);
	else if (action == 5)
		printf("\e[33m%.f \e[96m%ld \e[0;35mis thinking\e[39m\n", ft_time_p(p, 1), p->pos + 1);
}
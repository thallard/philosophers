/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:58:33 by thallard          #+#    #+#             */
/*   Updated: 2021/03/26 23:41:39 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

int	ft_take_forks(t_philos *p)
{
	sem_wait(p->sem);
	sem_wait(p->global->forks);
	print_log(p, FORK);
	sem_wait(p->global->forks);
	print_log(p, FORK);
	p->tdie = ft_time_p(p, 1) + p->info->time_die;
	p->times_eat++;
	print_log(p, EAT);
	usleep(p->info->time_eat * 1000);
	sem_post(p->global->forks);
	sem_post(p->global->forks);
	sem_post(p->sem);
	return (0);
}

void	ft_sleep(t_philos *p)
{
	sem_wait(p->sem);
	print_log(p, SLEEP);
	usleep(p->info->time_sleep * 1000);
	sem_post(p->sem);
}


void	print_log(t_philos *p, int action)
{
	sem_wait(p->global->sem);
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
	sem_close(p->global->sem);
}

int	quit(t_global *g)
{
	int		i;

	sem_close(g->forks);
	sem_close(g->sem);
	i = -1;
	while (++i < g->info->nb_philo)
		sem_close(g->philos[i]->sem);
	sem_unlink("global");
	sem_unlink("fork");
	sem_unlink("philo");
	return (0);
}

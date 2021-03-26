/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads_and_atoi.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:00:28 by thallard          #+#    #+#             */
/*   Updated: 2021/03/26 16:24:05 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_two.h"

pthread_t	ft_create_thread(t_global *global)
{
	pthread_t	thread;

	thread = malloc_lst(sizeof(pthread_t), global);
	if (!thread)
		return (NULL);
	return (thread);
}

int	ft_fill_threads(t_global *global)
{
	int		i;

	i = -1;
	global->threads = malloc_lst(sizeof(pthread_t) \
			 * (global->info->nb_philo + 1), global);
	if (!global->threads)
		return (0);
	while (++i < global->info->nb_philo)
		global->threads[i] = ft_create_thread(global);
	global->threads[i] = NULL;
	return (1);
}

static int	ft_is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f')
		return (0);
	else if (c == '\r')
		return (0);
	return (1);
}

static int	ft_str_is_numeric(char c)
{
	if (c < '0' || c > '9')
		return (0);
	return (1);
}

long	ft_atoi(const char *str)
{
	long		nb;
	long		signe;
	long		i;
	long		recur;

	recur = 0;
	i = 0;
	nb = 0;
	signe = 1;
	while (!ft_is_whitespace(str[i]))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			signe = -signe;
		recur++;
	}
	if (recur >= 2)
		return (0);
	while (ft_str_is_numeric(str[i]))
		nb = nb * 10 + (str[i++] - '0');
	return (nb * signe);
}

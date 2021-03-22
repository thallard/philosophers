/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 14:45:14 by thallard          #+#    #+#             */
/*   Updated: 2021/03/22 12:58:11 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

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
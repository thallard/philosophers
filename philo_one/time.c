/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 14:45:14 by thallard          #+#    #+#             */
/*   Updated: 2021/03/01 10:38:47 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

double	ft_time(t_global *g, int boolstart)
{
	struct timeval end;
	(void)g;
		gettimeofday (&end, NULL);
	if (boolstart)
		return ((double)(end.tv_usec - g->start_usec) / 1000 + (double) (end.tv_sec - g->start_sec) * 1000);
	
	return (end.tv_usec);

}

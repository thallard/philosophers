/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:03:45 by thallard          #+#    #+#             */
/*   Updated: 2021/02/25 16:27:17 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int main(int argc, char **argv)
{
	t_infos_philo	info;
	t_global		global;
	
	dprintf(1, "dbeug de argc = %d\n", argc);
	if (argc > 6 || argc <= 5)
	{
		printf("erreur de parametres\n");
		return (0);
	} 
	ft_init_infos_philo(&info, argv);
	dprintf(1, "[%ld] [%ld] [%ld] [%ld] [%ld]\n", info.nb_philo, info.time_die, info.time_eat, info.time_sleep, info.nb_eat);
}
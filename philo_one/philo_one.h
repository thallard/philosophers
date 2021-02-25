/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:04:06 by thallard          #+#    #+#             */
/*   Updated: 2021/02/25 16:12:49 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>


typedef struct		s_infos_philo
{
	long			nb_philo;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			nb_eat;
}					t_infos_philo;

typedef struct		s_malloc
{
	void			*content;
	struct s_malloc	*next;
}					t_malloc;

typedef struct		s_global
{
	t_malloc		*lst_free;
	t_infos_philo	*info;
}					t_global;

/*
* Utils
*/
void		*add_lst_to_free(t_global *global, void *ptr);
void		*lst_malloc(int size, t_global *global);
void		ft_exit(t_global *global);
long		ft_atoi(const char *str);

/*
** Setters
*/
void		ft_init_infos_philo(t_infos_philo *info, char **argv);

/*
** Linked list utils
*/
t_malloc	*ft_lstnew(void *content);
t_malloc	*ft_lstlast(t_malloc *lst);
void		ft_lstadd_back(t_malloc **alst, t_malloc *new);

#endif
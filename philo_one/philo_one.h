/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:04:06 by thallard          #+#    #+#             */
/*   Updated: 2021/03/01 15:19:07 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct		s_philos
{
	pthread_t		*thread;
	int				pos;
	int				tdie;
	int				teat;
	int				tthink;
	int				tsleep;
	int				times_eat;
}					t_philos;

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
	t_philos		**philos;
	t_malloc		*lst_free;
	t_infos_philo	*info;
	pthread_t		**threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*lock;
	int			i;
	double		start_usec;
	double			start_sec;
}					t_global;

/*
* Utils
*/
void		*add_lst_to_free(t_global *global, void *ptr);
void		*malloc_lst(int size, t_global *global);
void		ft_exit(t_global *global);
void		ft_fin(t_global *g, int pos);
long		ft_atoi(const char *str);

pthread_t	*ft_create_thread(t_global *global);

/*
** Setters
*/
void		ft_init_infos_philo(t_infos_philo *info, t_global *global, char **argv);
t_philos	*ft_init_philos(t_global *g, int pos);
/*
** Linked list utils
*/
t_malloc	*ft_lstnew(void *content);
t_malloc	*ft_lstlast(t_malloc *lst);
void		ft_lstadd_back(t_malloc **alst, t_malloc *new);

/*
** Time utils
*/
double	ft_time(t_global *g, int boolstart);

#endif
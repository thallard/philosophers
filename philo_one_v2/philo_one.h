/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 11:55:42 by thallard          #+#    #+#             */
/*   Updated: 2021/03/20 15:19:30 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct		s_infos_philo
{
	long			nb_philo;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			nb_eat;
}					t_infos_philo;


typedef struct		s_philos
{
	long			pos;
	long			tdie;
	long			teat;
	long			tthink;
	long			tsleep;
	long			times_eat;
	long			times_to_eat;
	long			alive;
	double			start_usec;
	double			start_sec;
	struct s_philos		**philos;
	t_infos_philo	*info;
	pthread_t		thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*locks;

}					t_philos;


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
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*safe;
	int				i;
	double			start_usec;
	double			start_sec;
}					t_global;

void	*malloc_lst(int size, t_global *global);
void	*add_lst_to_free(t_global *global, void *ptr);
int		ft_exit(t_global *g);

long				ft_atoi(const char *str);
double		ft_time_g(t_global *g, int boolstart);
double		ft_time_p(t_philos *p, int boolstart);
t_malloc	*ft_lstmalloc_new(void *content);
void	ft_lstmalloc_add_back(t_malloc **alst, t_malloc *new);
t_malloc	*ft_lstmalloc_last(t_malloc *lst);
void		ft_lstmalloc_clear(t_malloc **lst, void (*del)(void *));

#endif
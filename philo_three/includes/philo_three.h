/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 11:55:42 by thallard          #+#    #+#             */
/*   Updated: 2021/03/26 16:44:07 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H
# define FORK 1
# define EAT 3
# define SLEEP 4
# define THINK 5
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/types.h>
# include <signal.h>

typedef struct s_infos_philo
{
	long			nb_philo;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			nb_eat;
}	t_infos_philo;

typedef struct s_philos
{
	long			pos;
	double			tdie;
	long			times_eat;
	double			start_usec;
	double			start_sec;
	t_infos_philo	*info;
	pthread_t		thread;
	sem_t			*forks;
	sem_t			*sem;
	struct s_global	*global;
}	t_philos;

typedef struct s_malloc
{
	void			*content;
	struct s_malloc	*next;
}	t_malloc;

typedef struct s_global
{
	t_philos		**philos;
	t_malloc		*lst_free;
	t_infos_philo	*info;
	pthread_t		*threads;
	sem_t			*forks;
	sem_t			*sem;
	int				i;
	double			start_usec;
	double			start_sec;
	pid_t			*fork;
}	t_global;

void				*malloc_lst(int size, t_global *global);
void				*add_lst_to_free(t_global *global, void *ptr);
int					quit(t_global *g);
int					error_malloc(t_global *g, int freeall);

long				ft_atoi(const char *str);
double				ft_time_g(t_global *g, int boolstart);
double				ft_time_p(t_philos *p, int boolstart);
t_malloc			*ft_lstmalloc_new(void *content);
void				ft_lstmalloc_add_back(t_malloc **alst, t_malloc *new);
t_malloc			*ft_lstmalloc_last(t_malloc *lst);
int					ft_lstmalloc_clear(t_malloc **lst, void (*del)(void *), \
						t_global *g);

pthread_mutex_t		ft_create_fork(t_global *g);
int					ft_fill_forks(t_global *g);
pthread_mutex_t		*ft_fill_mutex(t_global *g);
pthread_t			ft_create_thread(t_global *global);
int					ft_fill_threads(t_global *global);

int					ft_take_forks(t_philos *p);
void				ft_sleep(t_philos *p);
void				ft_think(t_philos *p);
void				print_log(t_philos *p, int action);

int					ft_init_infos_philo(t_infos_philo *info, t_global *g, \
						char **argv, int argc);
t_philos			*ft_init_philos(t_global *g, int pos);
#endif
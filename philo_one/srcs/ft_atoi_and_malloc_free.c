/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_and_malloc_free.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:10:32 by thallard          #+#    #+#             */
/*   Updated: 2021/03/26 10:52:48 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

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

void	*malloc_lst(int size, t_global *global)
{
	void		*ptr;

	ptr = malloc(size);
	if (!(ptr))
		return (NULL);
	if (!(add_lst_to_free(global, ptr)))
		return (NULL);
	return (ptr);
}

void	*add_lst_to_free(t_global *global, void *ptr)
{
	t_malloc	*new;

	new = ft_lstmalloc_new(ptr);
	if (!(new))
	{
		free(ptr);
		return (NULL);
	}
	ft_lstmalloc_add_back(&global->lst_free, new);
	return (ptr);
}

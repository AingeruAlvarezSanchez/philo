/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initials.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:15:31 by aalvarez          #+#    #+#             */
/*   Updated: 2022/06/02 14:58:25 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

static int	ft_initvalues(t_data *data)
{
	int	i;

	data->th = (pthread_t *)malloc(sizeof(pthread_t) * data->n_philos);
	if (!data->th)
		return (1);
	data->fork = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->fork)
	{
		free(data->th);
		return (1);
	}
	i = -1;
	while (++i < data->n_philos)
		pthread_mutex_init(&data->fork[i], NULL);
	pthread_mutex_init(&data->dead, NULL);
	pthread_mutex_init(&data->print, NULL);
	data->died = 0;
	data->eaten = 0;
	return (0);
}

static int	ft_checkargv(char **argv, t_data *data)
{
	data->n_philos = ft_atoi(argv[1]);
	if (data->n_philos == '0' || data->n_philos == -1 || data->n_philos == -2)
		return (1);
	data->t_die = ft_atoi(argv[2]);
	if (data->t_die == '0' || data->t_die == -1 || data->t_die == -2)
		return (1);
	data->t_eat = ft_atoi(argv[3]);
	if (data->t_eat == '0' || data->t_eat == -1 || data->t_eat == -2)
		return (1);
	data->t_sleep = ft_atoi(argv[4]);
	if (data->t_sleep == '0' || data->t_sleep == -1 || data->t_sleep == -2)
		return (1);
	if (!argv[5])
		data->m_eat = 0;
	else
	{
		data->m_eat = ft_atoi(argv[5]);
		if (data->m_eat == -2)
			return (1);
	}
	if (ft_initvalues(data))
		return (1);
	return (0);
}

int	ft_initials(int argc, char **argv, t_data *data)
{
	if (argc < 5)
	{
		printf("There are not enough arguments\n");
		return (1);
	}
	if (argc > 6)
	{
		printf("There are too many arguments\n");
		return (1);
	}
	if (ft_checkargv(argv, data))
		return (1);
	return (0);
}

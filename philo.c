/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:15:41 by aalvarez          #+#    #+#             */
/*   Updated: 2022/06/02 14:50:16 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	ft_routine2(t_philo *philo)
{
	if (philo->data->died)
		return (1);
	ft_sleep(philo);
	ft_isdead(philo);
	if (philo->data->died)
		return (1);
	ft_printstatus(philo, "is thinking");
	ft_isdead(philo);
	if (philo->data->died)
		return (1);
	return (0);
}

static void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	philo->eaten = 0;
	philo->time = ft_time();
	if (philo->id % 2 == 1)
		ft_usleep(philo->data->t_eat - 20, philo);
	while (1)
	{
		ft_isdead(philo);
		if (philo->data->died)
			return (NULL);
		ft_eating(philo);
		if (philo->data->n_philos == 1)
			return (NULL);
		if (philo->data->eaten == philo->data->n_philos)
			return (NULL);
		ft_isdead(philo);
		if (ft_routine2(philo))
			return (NULL);
	}
	return (NULL);
}

static int	ft_create_threads(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)malloc(sizeof(t_philo) * data->n_philos);
	if (!philo)
		return (1);
	i = -1;
	data->time = ft_time();
	while (++i < data->n_philos)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].lf = i;
		philo[i].rf = (i + 1) % data->n_philos;
		pthread_create(&data->th[i], NULL, ft_routine, &philo[i]);
	}
	i = -1;
	while (++i < data->n_philos)
		pthread_join(data->th[i], NULL);
	free(philo);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (ft_initials(argc, argv, &data))
		return (1);
	if (ft_create_threads(&data))
		return (1);
	free(data.fork);
	free(data.th);
	return (0);
}

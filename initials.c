#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_initvalues(t_data *data)
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
	return (0);
}

int	ft_checkargv(char **argv, t_data *data)
{
	data->n_philos = ft_atoi(argv[1]);
	if (data->n_philos == '0' || data->n_philos == -1)
		return (1);
	data->t_die = ft_atoi(argv[2]);
	if (data->t_die == '0' || data->t_die == -1)
		return (1);
	data->t_eat = ft_atoi(argv[3]);
	if (data->t_eat == '0' || data->t_eat == -1)
		return (1);
	data->t_sleep = ft_atoi(argv[4]);
	if (data->t_sleep == '0' || data->t_sleep == -1)
		return (1);
	if (!argv[5])
		data->m_eat = 0;
	else
		data->m_eat = ft_atoi(argv[5]);
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


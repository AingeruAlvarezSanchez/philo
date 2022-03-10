#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->lf]);
	printstatus(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->fork[philo->rf]);
	printstatus(philo, "has taken a fork");
	printstatus(philo, "is eating");
	ft_usleep(philo->data->t_eat);
	philo->time = ft_time();
	pthread_mutex_unlock(&philo->data->fork[philo->lf]);
	pthread_mutex_unlock(&philo->data->fork[philo->rf]);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	philo->eaten = 0;
	philo->time = ft_time();
	if (philo->id % 2 == 1)
		ft_usleep(philo->data->t_eat - 20);
	while (1)
	{
		ft_eating(philo);
		ft_sleep(philo);
		printstatus(philo, "is sleeping");// es que me daba pereza hacer una funcion de sleeping
		ft_usleep(philo->data->t_sleep);
		//if (philo->data->died)
		//	return (NULL);
		//if (ft_isdead(philo))
		//	return (NULL);
		//if (!philo->data->died)
		//	printstatus(philo, "in thinking");
	}
	return (NULL);
}

int	ft_create_threads(t_data *data)
{
	t_philo	*philo;
	int	i;

	philo = (t_philo *)malloc(sizeof(t_philo) * data->n_philos);
	if (!philo)
		return (1);
	data->time = ft_time();
	i = -1;
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

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	philo->eaten = 0;
	philo->time = ft_time();
	if (philo->id % 2 == 1)
		ft_usleep(philo->data->t_eat - 20);
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
		if (philo->data->died)
			return (NULL);
		ft_sleep(philo);
		ft_isdead(philo);
		if (philo->data->died)
			return (NULL);
		ft_printstatus(philo, "is thinking");
		ft_isdead(philo);
		if (philo->data->died)
			return (NULL);
	}
	return (NULL);
}

static int	ft_create_threads(t_data *data)
{
	t_philo	*philo;
	int	i;

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

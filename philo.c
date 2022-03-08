#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	philo->eaten = 0;
	if (philo->id % 2 == 1)
		usleep(2000);
	while (1)
	{
		if (philo->data->died)
			return (NULL);
		if (ft_isdead(philo))
			return (NULL);
		if (!philo->data->died)
			printf("%d Philo %d is thinking\n",
				(ft_time() - philo->data->time), philo->id);
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

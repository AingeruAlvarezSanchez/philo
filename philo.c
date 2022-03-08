#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	printf("Im philo n: %d\n", philo->id);
	return (NULL);
}

int	ft_create_threads(t_data *data)
{
	t_philo	*philo;
	int	i;

	philo = (t_philo *)malloc(sizeof(t_philo) * data->n_philos);
	if (!philo)
		return (1);
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

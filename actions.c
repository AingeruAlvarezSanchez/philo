#include "philo.h"
#include <stdio.h>

int	ft_isdead(t_philo *philo)
{
	if (philo->data->died)
		return (1);
	pthread_mutex_lock(&philo->data->dead);
	if ((ft_time() - philo->data->time) >= philo->data->t_die)
	{
		printf("%d Philo %d died\n",
			(ft_time() - philo->data->time), philo->id);
		philo->data->died = 1;
		//pthread_mutex_unlock(&philo->data->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead);
	return (0);
}

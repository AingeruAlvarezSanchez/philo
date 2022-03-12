#include "philo.h"
#include <stdio.h>

void	ft_isdead(t_philo *philo)
{
	if (philo->data->died)
		return ;
	pthread_mutex_lock(&philo->data->dead);
	if ((ft_time() - philo->time) >= philo->data->t_die)
	{
		ft_printstatus(philo, "died");
		philo->data->died = 1;
		pthread_mutex_unlock(&philo->data->dead);
		return ;
	}
	pthread_mutex_unlock(&philo->data->dead);
}

void	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->lf]);
	ft_isdead(philo);
	if (philo->data->died)
	{
		pthread_mutex_unlock(&philo->data->fork[philo->lf]);
		pthread_mutex_unlock(&philo->data->fork[philo->rf]);
		return ;
	}
	ft_printstatus(philo, "has taken a fork");
	if (philo->data->n_philos == 1)
	{
		ft_usleep(philo->data->t_die - (ft_time() - philo->time));
		ft_printstatus(philo, "died");
		return ;
	}
	pthread_mutex_lock(&philo->data->fork[philo->rf]);
	ft_isdead(philo);
	if (philo->data->died)
	{
		pthread_mutex_unlock(&philo->data->fork[philo->lf]);
		pthread_mutex_unlock(&philo->data->fork[philo->rf]);
		return ;
	}
	ft_printstatus(philo, "has taken a fork");
	ft_isdead(philo);
	if (philo->data->died)
	{
		pthread_mutex_unlock(&philo->data->fork[philo->lf]);
		pthread_mutex_unlock(&philo->data->fork[philo->rf]);
		return ;
	}
	ft_printstatus(philo, "is eating");
	ft_usleep(philo->data->t_eat);
	ft_isdead(philo);
	if (philo->data->died)
	{
		pthread_mutex_unlock(&philo->data->fork[philo->lf]);
		pthread_mutex_unlock(&philo->data->fork[philo->rf]);
		return ;
	}
	philo->time = ft_time();
	if (philo->data->m_eat != 0)
		philo->eaten += 1;
	if (philo->eaten == philo->data->m_eat && philo->data->m_eat != 0)
		philo->data->eaten += 1;
	pthread_mutex_unlock(&philo->data->fork[philo->lf]);
	pthread_mutex_unlock(&philo->data->fork[philo->rf]);
	if (philo->data->eaten == philo->data->n_philos)
	{
		pthread_mutex_unlock(&philo->data->fork[philo->lf]);
		pthread_mutex_unlock(&philo->data->fork[philo->rf]);
		return ;
	}
}

void	ft_sleep(t_philo *philo)
{
	ft_isdead(philo);
	if (philo->data->died)
		return ;
	ft_usleep(philo->data->t_sleep);
	ft_isdead(philo);
	if (philo->data->died)
		return ;
	ft_printstatus(philo, "is sleeping");
	ft_isdead(philo);
	if (philo->data->died)
		return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:12:22 by aalvarez          #+#    #+#             */
/*   Updated: 2022/06/02 15:01:00 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	ft_eating3(t_philo *philo)
{
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

static void	ft_eating2(t_philo *philo)
{
	ft_printstatus(philo, "has taken a fork");
	ft_isdead(philo);
	if (philo->data->died)
	{
		pthread_mutex_unlock(&philo->data->fork[philo->lf]);
		pthread_mutex_unlock(&philo->data->fork[philo->rf]);
		return ;
	}
	ft_printstatus(philo, "is eating");
	ft_usleep(philo->data->t_eat, philo);
	ft_isdead(philo);
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
		ft_usleep(philo->data->t_die - (ft_time() - philo->time), philo);
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
	ft_eating2(philo);
	ft_eating3(philo);
}

void	ft_sleep(t_philo *philo)
{
	ft_isdead(philo);
	if (philo->data->died)
		return ;
	ft_printstatus(philo, "is sleeping");
	ft_usleep(philo->data->t_sleep, philo);
	ft_isdead(philo);
	if (philo->data->died)
		return ;
	ft_isdead(philo);
	if (philo->data->died)
		return ;
}

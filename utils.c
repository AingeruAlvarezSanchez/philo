/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:22:28 by aalvarez          #+#    #+#             */
/*   Updated: 2022/06/02 14:47:14 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

static int	ft_tdiff(struct timeval t1)
{
	struct timeval	t2;

	gettimeofday(&t2, NULL);
	return ((t2.tv_sec * 1000 + t2.tv_usec / 1000)
		- (t1.tv_sec * 1000 + t1.tv_usec / 1000));
}

void	ft_usleep(int ms, t_philo *philo)
{
	struct timeval	t1;

	gettimeofday(&t1, NULL);
	while (ms > ft_tdiff(t1))
	{
		ft_isdead(philo);
		if (philo->data->died)
			return ;
		usleep(100);
	}
}

int	ft_printstatus(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->data->print);
	if (!philo->data->died)
		printf("%d Philo %d %s\n", ft_time() - philo->data->time, philo->id, s);
	pthread_mutex_unlock(&philo->data->print);
	return (1);
}

int	ft_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

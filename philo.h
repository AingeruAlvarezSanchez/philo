/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:12:15 by aalvarez          #+#    #+#             */
/*   Updated: 2022/06/02 14:47:33 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>

typedef struct s_data {
	int				n_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				m_eat;
	int				time;
	int				eaten;
	pthread_t		*th;
	pthread_mutex_t	*fork;
	pthread_mutex_t	dead;
	pthread_mutex_t	print;
	int				died;
}	t_data;

typedef struct s_philo {
	int		id;
	int		eaten;
	int		lf;
	int		rf;
	int		time;
	t_data	*data;
}	t_philo;

int		ft_initials(int argc, char **argv, t_data *data);
int		ft_atoi(const char *str);
int		ft_time(void);
void	ft_isdead(t_philo *philo);
void	ft_eating(t_philo *philo);
void	ft_sleep(t_philo *philo);
int		ft_printstatus(t_philo *philo, char *s);
void	ft_usleep(int ms, t_philo *philo);

#endif

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>

typedef struct s_data {
	int		n_philos;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		m_eat;
	pthread_t	*th;
	pthread_mutex_t	*fork;
	pthread_mutex_t	dead;
}	t_data;

int	ft_initials(int argc, char **argv, t_data *data);
int	ft_atoi(const char *str);

#endif

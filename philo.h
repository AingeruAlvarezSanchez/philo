#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>

typedef struct s_data {
	int		n_philos;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		m_eat;
	int		time;
	pthread_t	*th;
	pthread_mutex_t	*fork;
	pthread_mutex_t	dead;
	int		died;
}	t_data;

typedef struct s_philo {
	int	id;
	int	eaten;
	t_data	*data;
}	t_philo;

int	ft_initials(int argc, char **argv, t_data *data);
int	ft_atoi(const char *str);
int	ft_time(void);

#endif

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
	pthread_mutex_t	print;
	int		died;
}	t_data;

typedef struct s_philo {
	int	id;
	int	eaten;
	int	lf;
	int	rf;
	int	time;
	// esta variable se inicializa en ft_time, es decir, pilla referencia de tiempo. Es la vida del filosofo, cada vez que acaba de comer se iguala a ft_time.
	// Para comprobar si el filosofo ha muerto lo que tienes que hacer es ft_time() - philo->time <= philo->dead y si es true pues muere. No es asi de facil pero como ejemplo
	// Se inicializa en la routine de cada philo
	t_data	*data;
}	t_philo;

int	ft_initials(int argc, char **argv, t_data *data);
int	ft_atoi(const char *str);
int	ft_time(void);
int	ft_isdead(t_philo *philo);
int	printstatus(t_philo *philo, char *s);
void	ft_usleep(int ms);

#endif

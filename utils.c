#include "philo.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
//esta funcion la necesita el ft_usleep para calcular la diferencia de tiempo
static int ft_tdiff(struct timeval t1)
{
	struct timeval t2;

	gettimeofday(&t2, NULL);
	return ((t2.tv_sec * 1000 + t2.tv_usec / 1000) - (t1.tv_sec * 1000 + t1.tv_usec / 1000));
}
//funcion que hace tu propio usleep haciendo mucho usleep chiquitos para que sea asi mas preciso.
//pilla una referencia de tiempo, pilla otra y calcula su diferencia (obviamente la primera vez es 0), si esta es menor que el tiempo que quieres que haga el usleep en ms hace un usleep y vuelve 
//a pillar otra referencia de tiempo y la compara con la primera, para ver si hace otro usleep  y asi hasta que sea False
//Claro, la pregunta es porque no hacemos then un usleep de 1 y ya esta. Pues porque entonces harias una infinidad de vecex el ft_tdiff por segundo, que tiene dentro un gettimeofday y el programa iria FATAL
void	ft_usleep(int ms)
{
	struct timeval t1;

	gettimeofday(&t1, NULL);
	while (ms > ft_tdiff(t1))
		usleep(100);
}

int	printstatus(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->data->print);
	if (!philo->data->died)
		printf("%d %d %s\n", ft_time() - philo->data->time, philo->id, s);
	pthread_mutex_unlock(&philo->data->print);
	return (1);
}

int	ft_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
 }

int	ft_checknumeric(const char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			printf("One or more arguments are not a number\n");
			return (1);
		}
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	unsigned int		i;
	int			neg;
	unsigned long int	nb;

	i = 0;
	neg = 1;
	nb = 0;
	if (ft_checknumeric(str))
		return (-1);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	if (nb > 9223372036854775807 && neg == -1)
		return (0);
	if (nb > 9223372036854775807 && neg == 1)
		return (-1);
	return (nb * neg);
}

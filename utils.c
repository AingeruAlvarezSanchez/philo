#include "philo.h"
#include <stdio.h>

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

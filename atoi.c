/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvarez <aalvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:23:36 by aalvarez          #+#    #+#             */
/*   Updated: 2022/06/02 14:31:25 by aalvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static int	ft_checknumeric(const char *str)
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

static int	ft_createnum(const char *str, unsigned long int nb, int neg)
{
	unsigned int	i;

	i = 0;
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
	return (nb * neg);
}

int	ft_atoi(const char *str)
{
	int					neg;
	unsigned long int	nb;

	neg = 1;
	nb = 0;
	if (ft_checknumeric(str))
		return (-2);
	nb = ft_createnum(str, nb, neg);
	if (nb > 9223372036854775807 && neg == -1)
		return (0);
	if (nb > 9223372036854775807 && neg == 1)
		return (-1);
	return (nb);
}

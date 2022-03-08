#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_data	data;
	if (ft_initials(argc, argv, &data))
		return (1);
	printf("Hello philo project\n");
	free(data.fork);
	free(data.th);
	return (0);
}

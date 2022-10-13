#include "philo.h"

void	ft_perror(char *msg)
{
	int	len;

	len = 0;
	while (msg[len])
		len++;
	write(2, "Error: ", 7);
	write(2, msg, len);
	write(2, "\n", 1);
}

int	error_manager(int error)
{
	if (error == 1)
		ft_perror("Wrong amount of arguments");
	if (error == 2)
		ft_perror("Invalid input");
	if (error == 3)
		ft_perror("Error when intializing mutexes and threads");
	if (error == 4)
		ft_perror("Error when joining threads and destroying mutexes");
	return (error);
}
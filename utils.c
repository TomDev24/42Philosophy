#include "philo.h"

unsigned long	timestamp()
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_usleep(unsigned long ms){
	unsigned long tm_start;

	tm_start = timestamp();
	while (1)
	{
		if (timestamp() - tm_start >= ms)
			break;
		usleep(50);
	}	
}

int			ft_atoi(const char *str)
{
	int i;
	int sign;
	int res;

	res = 0;
	i = 0;
	sign = 1;
	while (str[i] == '\n' || str[i] == ' ' || str[i] == '\t'
			|| str[i] == '\r' || str[i] == '\f' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
		sign = (str[i++] == '+') ? 1 : -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	return (res * sign);
}

void	lock_print(char *s, int	philo_id, t_params *params){
	pthread_mutex_lock(&params->write);
	printf("%ld ", timestamp() - params->tm_start);
	printf("%d ", philo_id + 1);
	printf("%s\n", s);
	pthread_mutex_unlock(&params->write);
}
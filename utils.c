#include "philo.h"

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

#include "philo.h"

int	init_mutexes(t_params *params)
{
	int i;

	i = -1;
	while (++i < params->philo_amount)
	{
		if (pthread_mutex_init(&(params->forks[i]), NULL))
			return (3);
	}
	if (pthread_mutex_init(&(params->write), NULL))
		return (3);
	if (pthread_mutex_init(&(params->access), NULL))
		return (3);
	return (0);
}

int	init_philos(t_params *params)
{
	int i;

	i = -1;
	while (++i < params->philo_amount)
	{
		params->philos[i].id = i;
        params->philos[i].min_fork = i; 
        params->philos[i].max_fork = (i + 1) % params->philo_amount; 
        if ((i + 1) % params->philo_amount < i){
            params->philos[i].min_fork = (i + 1) % params->philo_amount; 
            params->philos[i].max_fork = i; 
        }
		params->philos[i].c_eat = 0;
		params->philos[i].tm_last_eat = 0;
		params->philos[i].params = params;
	}
	return (0);
}

int init(t_params *params){
    params->all_alive = 1;
	params->rounds_finish = 0;
    if (init_mutexes(params))
        return 3;
    init_philos(params);
    return 0;
}
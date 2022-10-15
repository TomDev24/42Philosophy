#include "philo.h"

int    p_eating(t_philo *philo, t_params *params){

    pthread_mutex_lock(&(params->forks[philo->min_fork]));
    lock_print("has taken a fork", philo->id, params);
    if (philo->min_fork == philo->max_fork)
        return 1 + pthread_mutex_unlock(&(params->forks[philo->max_fork]));
    pthread_mutex_lock(&(params->forks[philo->max_fork]));
    lock_print("has taken a fork", philo->id, params);
    lock_print("is eating", philo->id, params); 
    pthread_mutex_lock(&(params->access));
    philo->tm_last_eat = timestamp();
    pthread_mutex_unlock(&(params->access));
    //Check ft_usleep!!
    ft_usleep(params->eat_time);
    pthread_mutex_lock(&(params->access));
    philo->c_eat++;
    pthread_mutex_unlock(&(params->access));

    pthread_mutex_unlock(&(params->forks[philo->max_fork]));
    pthread_mutex_unlock(&(params->forks[philo->min_fork]));
    return 0;
}

void    *thread(void *philosoph){
    t_philo *philo;
    t_params *params;

    philo = philosoph;
    params = philo->params;
    if (philo->id % 2 != 0)
        usleep(params->eat_time * 1000);
    while(params->all_alive){
        if(p_eating(philo, params))
            break;
        if (!params->all_alive || params->rounds_finish)
            break;
        lock_print("is sleeping", philo->id, params);
        ft_usleep(params->sleep_time);
        lock_print("is thinking", philo->id, params);
    }
    return NULL;
}

int start_emulation(t_params *params){
    int     i;
	t_philo *philos;

    params->tm_start = timestamp();
    philos = params->philos;
    i = -1;
    while (++i < params->philo_amount){
        philos[i].tm_last_eat = timestamp();
		if (pthread_create(&(philos[i].thread), NULL, thread, &(philos[i])))
			return (3);
        //pthread_detach(philos[i].thread);
    }
    return 0;
}
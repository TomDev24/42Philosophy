#include "philo.h"

int     clean_up(t_params *p, t_philo *philos){
    int i;
    int code;

	i = -1;
    code = 0;
    //usleep(3000);
	while (++i < p->philo_amount)
		code += pthread_join(philos[i].thread, NULL);
	i = -1;
	while (++i < p->philo_amount)
		code += pthread_mutex_destroy(&p->forks[i]);
	code += pthread_mutex_destroy(&p->write);
    code += pthread_mutex_destroy(&p->access);
    return code;
}

void    death_monitor(t_params *p, t_philo *philos){
    int i;
    int j;

    while(!p->rounds_finish){
        i = -1;
        j = 0;
		while (++i < p->philo_amount && p->all_alive)
		{
			pthread_mutex_lock(&(p->access));
            if (p->round_amount != 0 && philos[i].c_eat >= p->round_amount)
                j++;
            if (timestamp() - philos[i].tm_last_eat > p->die_time)
			{
                lock_print("died", i, p);
				p->all_alive = 0;
			}
            pthread_mutex_unlock(&(p->access));
		}
        if (!p->all_alive)
            break;
        // i = 0;
        // while (p->round_amount != 0 && i < p->philo_amount){
        //     pthread_mutex_lock(&(p->access));
        //     if (philos[i].c_eat >= p->round_amount)
        //         i++;
        //     pthread_mutex_unlock(&(p->access));
		// }
        if (j == p->philo_amount)
            p->rounds_finish = 1;
        usleep(800);
    }
}

int get_params(int argc, char **argv, t_params *params){
    params->philo_amount = ft_atoi(argv[1]);
    params->die_time = ft_atoi(argv[2]);
    params->eat_time = ft_atoi(argv[3]);
    params->sleep_time = ft_atoi(argv[4]);
    if (params->philo_amount <= 0 || params->die_time <= 0
		|| params->eat_time <= 0 || params->sleep_time <= 0
		|| params->philo_amount > 250)
		return 2;
    if (argc == 6){
        params->round_amount = ft_atoi(argv[5]);
        if (params->round_amount <= 0)
            return 2;
    } else {
        params->round_amount = 0;
    }
    return 0;
}

int main(int argc, char **argv){
    t_params params;
    
    if (argc < 5 || argc > 6) 
        return(error_manager(1));
    if (get_params(argc, argv, &params))
        return(error_manager(2));
    if (init(&params))
        return(error_manager(3));
    if (start_emulation(&params))
        return(error_manager(3));

    death_monitor(&params, params.philos);
    if (clean_up(&params, params.philos))
        return(error_manager(4));
    return 0;
}
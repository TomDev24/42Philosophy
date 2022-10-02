#include "philo.h"

t_params* get_params(int argc, char **argv){
    t_params *params;

    params = malloc(sizeof(t_params));
    if (!params)
        exit(1);
    if (argc >= 2)
        params->philo_amount = ft_atoi(argv[1]);
    if (argc >= 3)
        params->die_time = ft_atoi(argv[2]);
    if (argc >= 4)
        params->eat_time = ft_atoi(argv[3]);
    if (argc >= 5)
        params->sleep_time = ft_atoi(argv[4]);
    if (argc == 6)
        params->round_amount = ft_atoi(argv[5]);

    if (argc > 6)
        printf("Invalid amount of args\n");
    return params;
}

t_philo **init_philos(t_global *global){
    t_philo **philos;
    int     i;

    philos = malloc(sizeof(t_philo*) * global->params->philo_amount);
    if (!philos)
        exit(1);
    i = -1;
    while (++i < global->params->philo_amount){
        philos[i] = malloc(sizeof(t_philo));
        if (!philos[i])
            exit(1);
        philos[i]->id = i;
        philos[i]->state = THINK;
        philos[i]->global = global;
    }
    return philos;
}

void    *routine(void *philosoph){
    t_philo     *philo;
    t_global    *global;

    philo = (t_philo*)philosoph;
    global = philo->global;
    while (1){
        gettimeofday(&(global->time), NULL);
        printf("%ld %d ", global->time.tv_sec * 1000 + global->time.tv_usec / 1000, philo->id);
        if (philo->state == SLEEP){
            printf("is sleeping\n");
            usleep(global->params->sleep_time * 1000);
            philo->state = THINK;
        }
        else if (philo->state == EAT){
            printf("is eating\n");
            usleep(global->params->eat_time * 1000);
            philo->state = SLEEP;
        }
        else if (philo->state == THINK){
            printf("is thinking\n");
            //EMULATION
            usleep(global->params->eat_time * 1000);
            philo->state = EAT;
        }
    }
}

int main(int argc, char **argv){
    t_global        global;
    t_philo         **philos;
    pthread_t       *threads;
    int             i;

    global.params = get_params(argc, argv);
    philos = init_philos(&global);
    threads = malloc(sizeof(pthread_t) * global.params->philo_amount);
    if (!threads)
        return 1;
    global.params->die_time = 3000;
    global.params->eat_time = 1000;
    global.params->sleep_time = 1500;

    i = -1;
    while (++i < global.params->philo_amount)
        pthread_create(&threads[i], NULL, &routine, philos[i]);
    i = -1;
    while (++i < global.params->philo_amount)
        pthread_join(threads[i], NULL);
    return  0;
}
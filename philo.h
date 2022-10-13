#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>

struct s_params;

typedef struct s_philo
{
    int             id;
    //int             lfork_i;
    //int             rfork_i;
    int             min_fork;
    int             max_fork;
    int             c_eat;
    unsigned long   tm_last_eat;
    pthread_t       thread;
    struct s_params *params;
}               t_philo;

typedef struct s_params
{
    int    philo_amount;
    int    die_time;
    int    eat_time;
    int    sleep_time;
    int    round_amount;
    unsigned long       tm_start;
    t_philo		        philos[250];
    pthread_mutex_t		forks[250];
    pthread_mutex_t		write;
    pthread_mutex_t		access;
    char                all_alive;
    char                rounds_finish;
}               t_params;

unsigned long	timestamp();
void	        ft_usleep(unsigned long ms);
int		        ft_atoi(const char *str);
void	        lock_print(char *s, int	philo_id, t_params *params);

//Errors
void	ft_perror(char *msg);
int     error_manager(int error);

//Init
int     init(t_params *params);

//Philo Cycles
int start_emulation(t_params *params);

#endif
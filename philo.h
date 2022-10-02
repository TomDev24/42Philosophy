#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>

enum {
    EAT,
    SLEEP,
    THINK
};

typedef struct s_params
{
    int    philo_amount;
    unsigned int    die_time;
    unsigned int    eat_time;
    unsigned int    sleep_time;
    unsigned int    round_amount;
}               t_params;

typedef struct s_global
{
    t_params        *params;
    struct timeval  time;

}               t_global;

typedef struct s_philo
{
    int         id;
    int         state;
    t_global    *global;
}               t_philo;

int			ft_atoi(const char *str);

#endif
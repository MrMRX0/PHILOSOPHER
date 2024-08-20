/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:04:25 by ibougajd          #+#    #+#             */
/*   Updated: 2024/08/20 03:40:46 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

#define ERROR_MSG "philo: usage: ./philo <number_of_philosophers> <time_to_die> \
 <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]"

typedef struct t_list
{
	pthread_t		philo;
	pthread_mutex_t	forks;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	flag_mutex;
	pthread_mutex_t	curent_mutex;
	pthread_mutex_t	kla_mutex;
	int				id;
	long			last_meal;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_of_philos;
	int				flag;
	long			curent;
	int				n_of_meals;
	int				kla;
}					t_data;

void	*monitoring_function(void *arg);
long	get_current_time_in_milliseconds(void);
int		eating(t_data *data);
int		sleeping(t_data *data);
int		thinking(t_data *data);
int		take_left_fork(t_data *data, int check);
int		take_right_fork(t_data *data, int check);
int		sleep_function(t_data *data, int time);
int		check_death(t_data *data);
long	ft_atoi(const char *str, int *b);
long	get_current_time_in_milliseconds(void);
int		sleep_function(t_data *data, int time);
int		check_death(t_data *data);
void	put_down_forks(t_data *data);
int		initialize_data(t_data *data, int number_of_philosophers, char **av);
void	initialize_mutexes(t_data *data, int number_of_philosophers);
void	create_and_join_threads(t_data *data, int number_of_philosophers);
void	free_and_destroy_data(t_data *data, int n);
void	*action_function(void *arg);
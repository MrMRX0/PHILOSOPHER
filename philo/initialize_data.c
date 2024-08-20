/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 19:11:18 by ibougajd          #+#    #+#             */
/*   Updated: 2024/08/20 03:40:33 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialize_mutexes(t_data *data, int number_of_philosophers)
{
	int	i;

	i = 0;
	while (i < number_of_philosophers)
	{
		pthread_mutex_init(&data[i].forks, NULL);
		pthread_mutex_init(&data[i].meal_mutex, NULL);
		pthread_mutex_init(&data[i].flag_mutex, NULL);
		pthread_mutex_init(&data[i].curent_mutex, NULL);
		pthread_mutex_init(&data[i].kla_mutex, NULL);
		i++;
	}
	i = 0;
	while (i < number_of_philosophers)
	{
		data[i].left_fork = &data[i].forks;
		data[i].right_fork = &data[(i + 1) % number_of_philosophers].forks;
		i++;
	}
}

int	initialize_data(t_data *data, int number_of_philosophers, char **av)
{
	int	number_of_meals;
	int	time_to_sleep;
	int	time_to_die;
	int	time_to_eat;
	int	b;

	b = 0;
	time_to_die = ft_atoi(av[2], &b);
	time_to_eat = ft_atoi(av[3], &b);
	time_to_sleep = ft_atoi(av[4], &b);
	if (av[5])
		number_of_meals = ft_atoi(av[5], &b);
	if (b)
		return (printf("%s\n", ERROR_MSG), 1);
	while (b < number_of_philosophers)
	{
		data[b].time_to_die = time_to_die;
		data[b].time_to_eat = time_to_eat;
		data[b].time_to_sleep = time_to_sleep;
		data[b].n_of_meals = number_of_meals;
		data[b].n_of_philos = number_of_philosophers;
		data[b].flag = 0;
		b++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 19:21:01 by ibougajd          #+#    #+#             */
/*   Updated: 2024/08/20 03:39:28 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	add_delay(t_data *data)
{
	pthread_mutex_lock(&data->curent_mutex);
	data->curent = get_current_time_in_milliseconds();
	pthread_mutex_unlock(&data->curent_mutex);
	pthread_mutex_lock(&data->meal_mutex);
	data->last_meal = get_current_time_in_milliseconds();
	pthread_mutex_unlock(&data->meal_mutex);
	if (data->n_of_philos % 2 == 0 && data->id % 2 == 1)
	{
		if (data->n_of_philos > 10)
			sleep_function(data, 4);
		else
			usleep(1000);
	}
	else if (data->n_of_philos % 2 == 1 && data->id % 2 == 0)
	{
		if (data->n_of_philos > 10)
			sleep_function(data, 4);
		else
			usleep(1000);
	}
}

int	take_right_fork_first(t_data *data)
{
	if (take_right_fork(data, 0))
		return (1);
	if (take_left_fork(data, 1))
		return (1);
	return (0);
}

int	take_left_fork_first(t_data *data)
{
	if (take_left_fork(data, 0))
		return (1);
	if (data->n_of_philos == 1)
		return (1);
	if (take_right_fork(data, 1))
		return (1);
	return (0);
}

void	check_meals(t_data *data)
{
	if (data->n_of_meals != 0)
		data->n_of_meals--;
	if (!data->n_of_meals)
	{
		pthread_mutex_lock(&data->kla_mutex);
		data->kla = 1;
		pthread_mutex_unlock(&data->kla_mutex);
	}
}

void	*action_function(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	add_delay(data);
	pthread_mutex_lock(&data->kla_mutex);
	data->kla = 0;
	pthread_mutex_unlock(&data->kla_mutex);
	while (data->n_of_meals != 0)
	{
		if (thinking(data))
			return (NULL);
		if (data->id % 2 == 0 && take_right_fork_first(data) == 1)
			return (NULL);
		else if (data->id % 2 == 1 && take_left_fork_first(data) == 1)
			return (NULL);
		if (eating(data))
			return (NULL);
		put_down_forks(data);
		if (sleeping(data))
			return (NULL);
		check_meals(data);
	}
	return (NULL);
}

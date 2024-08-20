/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:06:13 by ibougajd          #+#    #+#             */
/*   Updated: 2024/08/20 06:06:52 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_data *data)
{
	long	curent_time;

	curent_time = 0;
	if (check_death(data))
	{
		pthread_mutex_unlock(data->right_fork);
		pthread_mutex_unlock(data->left_fork);
		return (1);
	}
	curent_time = (get_current_time_in_milliseconds() - data->curent);
	printf(GREEN "%ld %d is eating\n" RESET, curent_time, data->id);
	pthread_mutex_lock(&data->meal_mutex);
	data->last_meal = get_current_time_in_milliseconds();
	pthread_mutex_unlock(&data->meal_mutex);
	if (sleep_function(data, data->time_to_eat) == 1)
	{
		pthread_mutex_unlock(data->right_fork);
		pthread_mutex_unlock(data->left_fork);
		return (1);
	}
	return (0);
}

int	sleeping(t_data *data)
{
	long	curent_time;

	curent_time = 0;
	if (check_death(data))
		return (1);
	curent_time = (get_current_time_in_milliseconds() - data->curent);
	printf(MAGENTA "%ld %d is sleeping\n" RESET, curent_time, data->id);
	if (sleep_function(data, data->time_to_sleep) == 1)
		return (1);
	return (0);
}

int	thinking(t_data *data)
{
	long	curent_time;

	curent_time = 0;
	if (check_death(data))
		return (1);
	curent_time = (get_current_time_in_milliseconds() - data->curent);
	printf(BLUE "%ld %d is thinking\n" RESET, curent_time, data->id);
	return (0);
}

int	take_left_fork(t_data *data, int check)
{
	long	curent_time;

	curent_time = 0;
	if (check_death(data))
	{
		if (check)
			pthread_mutex_unlock(data->right_fork);
		return (1);
	}
	pthread_mutex_lock(data->left_fork);
	if (check_death(data))
	{
		pthread_mutex_unlock(data->left_fork);
		if (check)
			pthread_mutex_unlock(data->right_fork);
		return (1);
	}
	curent_time = (get_current_time_in_milliseconds() - data->curent);
	printf(WHITE "%ld %d has taken a left forkkk\n" RESET, curent_time,
		data->id);
	return (0);
}

int	take_right_fork(t_data *data, int check)
{
	long	curent_time;

	curent_time = 0;
	if (data->id % 2 == 1)
		usleep(100);
	if (check_death(data))
	{
		if (check)
			pthread_mutex_unlock(data->left_fork);
		return (1);
	}
	pthread_mutex_lock(data->right_fork);
	if (check_death(data))
	{
		pthread_mutex_unlock(data->right_fork);
		if (check)
			pthread_mutex_unlock(data->left_fork);
		return (1);
	}
	curent_time = (get_current_time_in_milliseconds() - data->curent);
	printf(WHITE "%ld %d has taken a right fork\n" RESET, curent_time,
		data->id);
	return (0);
}

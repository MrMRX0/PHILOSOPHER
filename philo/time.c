/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:51:10 by ibougajd          #+#    #+#             */
/*   Updated: 2024/08/20 02:26:19 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *str, int *b)
{
	int		i;
	long	r;

	i = 0;
	r = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			r = r * 10 + str[i] - '0';
		else
			return (*b = 1);
		if (r > 2147483647)
			return (*b = 1);
		i++;
	}
	return (r);
}

long	get_current_time_in_milliseconds(void)
{
	struct timeval	tv;
	int				res;

	gettimeofday(&tv, NULL);
	res = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (res);
}

int	sleep_function(t_data *data, int time)
{
	int	db;
	int	curent;
	int	gbil;

	pthread_mutex_lock(&data->curent_mutex);
	curent = data->curent;
	pthread_mutex_unlock(&data->curent_mutex);
	gbil = (get_current_time_in_milliseconds() - curent);
	db = 0;
	while (1)
	{
		db = (get_current_time_in_milliseconds() - curent);
		if ((db - gbil) >= time)
			break ;
		pthread_mutex_lock(&data->flag_mutex);
		if (data->flag)
		{
			pthread_mutex_unlock(&data->flag_mutex);
			return (1);
		}
		pthread_mutex_unlock(&data->flag_mutex);
		usleep(100);
	}
	return (0);
}

int	check_death(t_data *data)
{
	pthread_mutex_lock(&data->flag_mutex);
	if (data->flag)
	{
		pthread_mutex_unlock(&data->flag_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->flag_mutex);
	return (0);
}

void	put_down_forks(t_data *data)
{
	pthread_mutex_unlock(data->left_fork);
	pthread_mutex_unlock(data->right_fork);
}

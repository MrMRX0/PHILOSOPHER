/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 20:49:01 by ibougajd          #+#    #+#             */
/*   Updated: 2024/08/21 01:12:00 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_meal(t_data *data)
{
	int	j;
	int	b;
	int	n;

	b = 0;
	j = 0;
	n = data[0].n_of_philos;
	while (1)
	{
		pthread_mutex_lock(&data[b].kla_mutex);
		j = data[b].kla;
		pthread_mutex_unlock(&data[b].kla_mutex);
		if (j == 0)
			break ;
		b++;
	}
	if (b == n)
		return (1);
	return (0);
}

void	philo_death_action(t_data *data, int i, int n)
{
	long	res;
	int		j;

	res = 0;
	j = 0;
	while (j < n)
	{
		pthread_mutex_lock(&data[j].flag_mutex);
		data[j].flag = -1;
		pthread_mutex_unlock(&data[j].flag_mutex);
		j++;
	}
	pthread_mutex_lock(&data[i].curent_mutex);
	res = ((get_current_time_in_milliseconds()) - (data[i].curent));
	pthread_mutex_unlock(&data[i].curent_mutex);
	usleep(3000);
	printf(RED "%ld %d is died\n" RESET, res, i + 1);
}

void	norm(t_data *data, int *flag, int *meal, int i)
{
	pthread_mutex_lock(&data[i].kla_mutex);
	*flag = (data[i].kla);
	pthread_mutex_unlock(&data[i].kla_mutex);
	pthread_mutex_lock(&data[i].meal_mutex);
	*meal = (data[i].last_meal);
	pthread_mutex_unlock(&data[i].meal_mutex);
}

void	*monitoring_function(void *arg)
{
	t_data	*data;
	int		i;
	long	curent_time;
	int		last_meal;
	int		kla_flag;

	data = (t_data *)arg;
	i = 0;
	usleep(1000);
	while (1)
	{
		if (check_philo_meal(data) == 1)
			return (NULL);
		norm(data, &kla_flag, &last_meal, i);
		curent_time = get_current_time_in_milliseconds();
		if ((curent_time - last_meal) > (data[0].time_to_die) && kla_flag == 0)
			return (philo_death_action(data, i, data[0].n_of_philos), NULL);
		i++;
		if (i == data[0].n_of_philos)
			i = 0;
	}
	return (NULL);
}

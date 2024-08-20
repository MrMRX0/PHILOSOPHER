/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_join_threads.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 19:13:56 by ibougajd          #+#    #+#             */
/*   Updated: 2024/08/20 00:12:10 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_and_join_threads(t_data *data, int number_of_philosophers)
{
	pthread_t	monitor;
	int			i;

	i = 0;
	while (i < number_of_philosophers)
	{
		data[i].id = i + 1;
		pthread_create(&data[i].philo, NULL, action_function, &data[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitoring_function, data);
	i = 0;
	pthread_join(monitor, NULL);
	while (i < number_of_philosophers)
	{
		pthread_join(data[i].philo, NULL);
		i++;
	}
}

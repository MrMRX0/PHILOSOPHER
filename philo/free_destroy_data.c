/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_destroy_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 19:17:13 by ibougajd          #+#    #+#             */
/*   Updated: 2024/08/21 01:41:21 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_and_destroy_data(t_data *data, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&data[i].forks);
		pthread_mutex_destroy(&data[i].meal_mutex);
		pthread_mutex_destroy(&data[i].flag_mutex);
		pthread_mutex_destroy(&data[i].curent_mutex);
		pthread_mutex_destroy(&data[i].kla_mutex);
		i++;
	}
	pthread_mutex_destroy(data[0].mutex_0);
	pthread_mutex_destroy(data[0].mutex_1);
	pthread_mutex_destroy(data[0].mutex_2);
	pthread_mutex_destroy(data[0].mutex_3);
	free(data);
}

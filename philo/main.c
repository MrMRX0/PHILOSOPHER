/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibougajd <ibougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 06:21:51 by ibougajd          #+#    #+#             */
/*   Updated: 2024/08/20 06:56:44 by ibougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;
	int		number_of_philosophers;
	int		b;

	if (ac < 5 || ac > 6)
		return (printf("%s\n", ERROR_MSG), 1);
	b = 0;
	number_of_philosophers = ft_atoi(av[1], &b);
	if (b)
		return (printf("%s\n", ERROR_MSG), 1);
	data = malloc(number_of_philosophers * sizeof(t_data));
	if (!data)
		return (1);
	if (initialize_data(data, number_of_philosophers, av) == 1)
		return (1);
	initialize_mutexes(data, number_of_philosophers);
	initialize_mutexes_2(data, number_of_philosophers);
	create_and_join_threads(data, number_of_philosophers);
	free_and_destroy_data(data, number_of_philosophers);
}

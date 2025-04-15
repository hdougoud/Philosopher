/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:02:05 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/15 17:25:07 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_philosophers(t_data *data, int n_thread)
{
	int		i;
	

	data->philo = ft_calloc(1, sizeof(t_philo));
	if (!data->philo)
		print_error("Malloc : Allocation for **philo failed");
	i = 0;
	while (i < n_thread)
	{
		data->philo[i] = malloc(sizeof(t_philo)); //check leaks (free t_philo tab is possibly needed)
		if (!data->philo[i])
			print_error("Malloc : Allocation for philo[i] failed");
		if (pthread_create(&data->philo[i]->thread, NULL, execute_philo, (void *)data))
			print_error("Pthread : Thread creation failed");
		i++;
	}
}

void	init_struct(t_data *data)
{
	data->n_philosophers = 0;
	data->time_to_eat = 0;
	data->time_to_die = 0;
	data->time_to_sleep = 0;
	data->must_eat = 0;
	data->philo = NULL;
}
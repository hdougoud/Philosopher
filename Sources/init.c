/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:21:06 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/07 22:07:54 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include "../include/struct.h"

static int	init_data_strcut(t_data *data)
{
	if (gettimeofday(data->timer, NULL))
		return (print_error("gettimeofday : function failed"));
	if (pthread_mutex_init(&data->death_check.mutex, NULL))
		return (print_error("pthread_mutex_init : Initialisation failed"));
	if (pthread_mutex_init(&data->satiated.mutex, NULL))
	{
		pthread_mutex_destroy(&data->death_check.mutex);
		return (print_error("pthread_mutex_init : Initialisation failed"));
	}
	if (pthread_mutex_init(&data->print, NULL))
	{
		pthread_mutex_destroy(&data->satiated.mutex);
		pthread_mutex_destroy(&data->death_check.mutex);
		return (print_error("pthread_mutex_init : Initialisation failed"));
	}
	return (0);
}

int	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	data->philo = ft_calloc(data->philosophers, sizeof(t_philo));
	if (!data->philo)
		return (print_error("Malloc : allocation failed"));
	init_data_strcut(data);
	while (i < data->philosophers)
	{
		data->philo[i].data = data;
		if (pthread_create(&data->philo[i].thread_id, NULL, exec_thread, &data->philo[i]))
			return (1); //free and clear all
		
		i++;
	}
	return (0);
}

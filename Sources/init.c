/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:21:06 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/08 11:32:26 by hdougoud         ###   ########.fr       */
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

static int	init_philo_struct(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philosophers)
	{
		if (pthread_mutex_init(&data->philo[i].right_hand, NULL))
			return (print_error("pthread_mutex_init : Initialisation failed"));
		if (gettimeofday(&data->philo[i].last_meal.tv, NULL))
			return (print_error("gettimeofday : function failed"));
	}
	i = -1;
	while (++i < data->philosophers)
	{
		if (i != 0)
			data->philo[i].left_hand = &data->philo[i - 1].right_hand;
		else
			data->philo[0].left_hand = &data->philo[data->philosophers - 1].right_hand;
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
	if (init_data_strcut(data))
		return (1); //free_all
	if (init_philo_struct(data))
		return (1);
	while (i < data->philosophers)
	{
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		if (pthread_create(&data->philo[i].thread_id, NULL, exec_thread, &data->philo[i]))
			return (1); //free and clear all
		i++;
	}
	return (0);
}

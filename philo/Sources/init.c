/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:21:06 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/09 19:44:02 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../include/philo.h"
#include "../include/struct.h"

static void	init_failed(t_data *data, int i, int status)
{
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->satiated.mutex);
	pthread_mutex_destroy(&data->death_check.mutex);
	while (i >= 0)
	{
		if (status > 2)
			pthread_mutex_destroy(&data->philo[i].right_hand);
		if (status > 3)
			pthread_mutex_destroy(&data->philo[i].last_meal.mutex);
		status = 4;
		i--;
	}
}

static int	init_data_strcut(t_data *data)
{
	if (gettimeofday(&data->timer, NULL))
		return (print_error(&data->print, "gettimeofday : function fail"));
	if (pthread_mutex_init(&data->death_check.mutex, NULL))
		return (print_error(&data->print, "pthread : initialisation failed"));
	if (pthread_mutex_init(&data->satiated.mutex, NULL))
	{
		pthread_mutex_destroy(&data->death_check.mutex);
		return (print_error(&data->print, "pthread : initialisation failed"));
	}
	if (pthread_mutex_init(&data->print, NULL))
	{
		pthread_mutex_destroy(&data->satiated.mutex);
		pthread_mutex_destroy(&data->death_check.mutex);
		return (print_error(&data->print, "pthread : initialisation failed"));
	}
	data->satiated.var = 0;
	data->death_check.var = 0;
	return (0);
}

static int	init_philo_struct(t_data *data)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	while (++i < data->philosophers && !status)
	{
		if (pthread_mutex_init(&data->philo[i].right_hand, NULL))
			status = print_error(&data->print, "mutex_init : init failed") + 1;
		if (pthread_mutex_init(&data->philo[i].last_meal.mutex, NULL))
			status = print_error(&data->print, "mutex_init : init faied") + 2;
		if (gettimeofday(&data->philo[i].last_meal.tv, NULL))
			status = print_error(&data->print, "gettimeofday : fail") + 3;
	}
	i = -1;
	while (++i < data->philosophers && !status)
	{
		data->philo[i].left_hand = &data->philo[(i + data->philosophers - 1)
			% data->philosophers].right_hand;
	}
	if (status)
		return (init_failed(data, i, status), 1);
	return (0);
}

int	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	data->philo = ft_calloc(data->philosophers, sizeof(t_philo));
	if (!data->philo)
		return (print_error(&data->print, "Malloc : allocation failed"));
	if (init_data_strcut(data))
		return (free(data->philo), 1);
	if (init_philo_struct(data))
		return (free(data->philo), 1);
	while (i < data->philosophers)
	{
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		if (pthread_create(&data->philo[i].thread_id, NULL, exec_thread,
				&data->philo[i]))
		{
			pthread_mutex_lock(&data->death_check.mutex);
			data->death_check.var = 1;
			pthread_mutex_unlock(&data->death_check.mutex);
			return (print_error(&data->print, "pthread : creation failed"));
		}
		i++;
	}
	return (0);
}

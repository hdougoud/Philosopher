/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:16:57 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/12 09:01:31 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include "../include/struct.h"
#include "../include/thread.h"

static int	end_simulation(t_data *data)
{
	int	i;

	i = 0;
	print_activity(data->philo, DIED);
	pthread_mutex_lock(&data->death_check.mutex);
	data->death_check.var = 1;
	pthread_mutex_unlock(&data->death_check.mutex);
	while (i < data->philosophers)
	{
		if (pthread_join(data->philo[i].thread_id, NULL))
			return (print_error(&data->print, "pthread_join : unknow error"));
		i++;
	}
	if (data->satiated.var == data->philosophers)
		putstr_fd(1, GREEN"the simulation ended successfully\n"RESET);
	else
		putstr_fd(1, RED"A philosopher has died, end of simulation\n"RESET);
	return (0);
}

int	monitoring(t_data *data)
{
	int				i;
	int				timer;
	struct timeval	new;

	i = 0;
	timer = 0;
	while (timer < data->time_to_die)
	{
		usleep(500);
		if (i >= data->philosophers)
			i = 0;
		if (gettimeofday(&new, NULL))
		{
			free_all(data);
			return (print_error(&data->print, "gettimeofday : unknow error"));
		}
		pthread_mutex_lock(&data->philo[i].last_meal.mutex);
		timer = (new.tv_sec - data->philo[i].last_meal.tv.tv_sec) * 1000;
		timer += (new.tv_usec - data->philo[i].last_meal.tv.tv_usec) / 1000;
		pthread_mutex_unlock(&data->philo[i].last_meal.mutex);
	}
	if (end_simulation(data))
		return (1);
	return (0);
}

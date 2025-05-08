/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:16:57 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/08 14:39:58 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include "../include/struct.h"
#include "../include/thread.h"

static int	join_all_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philosophers)
	{
		if (pthread_join(data->philo[i].thread_id, NULL))
			return (print_error("pthread_join : function failed"));
		i++;
	}
	return (0);
}

int	monitoring(t_data *data)
{
	int				i;
	int				timer;
	struct timeval	new;

	i = -1;
	timer = 0;
	while(timer < data->time_to_die)
	{
		usleep(200);
		if (++i > data->philosophers)
			i = 0;
		if (gettimeofday(&new, NULL))
			return (1);
		pthread_mutex_lock(&data->philo[i].last_meal.mutex);
		timer = (new.tv_usec - data->philo[i].last_meal.tv.tv_sec) * 1000;
		timer += (new.tv_sec - data->philo[i].last_meal.tv.tv_usec) / 1000;
		pthread_mutex_unlock(&data->philo[i].last_meal.mutex);
	}
	pthread_mutex_lock(&data->death_check.mutex);
	
	pthread_mutex_unlock(&data->death_check.muetex);
	return (join_all_thread(data));
}

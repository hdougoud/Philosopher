/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:07:15 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/02 13:50:10 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/struct.h"
#include "../include/thread.h"

static int	did_everyone_eat(t_data *data)
{
	int	status;

	status = 0;
	if (data->args->must_eat > 0)
	{
		pthread_mutex_lock(&data->satiated->mutex);
		if (data->eated == data->args->must_eat && !data->objective_complete)
		{
			data->satiated->var += 1;
			data->objective_complete = 1;
		}
		if (data->satiated->var >= data->args->philosophers)
		{
			data->is_finished->var = 1;
			status = 1;
		}
		pthread_mutex_unlock(&data->satiated->mutex);
	}
	return (status);
}

int	is_ended(t_data *data)
{
	int	status;

	status = 0;
	pthread_mutex_lock(&data->is_finished->mutex);
	if (data->is_finished->var == 1)
		status = 1;
	if (status == 1)
	{
		pthread_mutex_unlock(&data->is_finished->mutex);
		return (status);
	}
	status = did_everyone_eat(data);
	pthread_mutex_unlock(&data->is_finished->mutex);
	return (status);
		
}

void	print_activity(t_data *data, char *activity)
{
	int				timer;
	struct timeval	temp;
	
	if (gettimeofday(&temp, NULL))
		return ;
	timer = (temp.tv_usec - data->timer->tv_usec) / 1000;
	timer += (temp.tv_sec - data->timer->tv_sec) * 1000;
	pthread_mutex_lock(data->print);
	if (!is_ended(data))
		printf("%dms %d %s\n", timer, data->philo_x, activity);
	pthread_mutex_unlock(data->print);
}

void	check_last_meal(t_data *data)
{
	int timer;
	
	if (is_ended(data))
		return ;
	timer = update_local_timer(&data->last_meal);
	if (timer > data->args->time_to_die)
	{
		print_activity(data, DIED);
		pthread_mutex_lock(&data->is_finished->mutex);
		data->is_finished->var = 1;
		pthread_mutex_unlock(&data->is_finished->mutex);
	}
}
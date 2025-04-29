/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:07:15 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/29 19:12:42 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/struct.h"
#include "../include/thread.h"

static int	is_everyone_ate(t_data *data)
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
			pthread_mutex_lock(&data->is_finished->mutex);
			data->is_finished->var = 1;
			pthread_mutex_unlock(&data->is_finished->mutex);
			pthread_mutex_unlock(&data->satiated->mutex);
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
	pthread_mutex_unlock(&data->is_finished->mutex);
	if (status == 1)
		return (status);
	return (is_everyone_ate(data));
		
}

void	print_activity(t_data *data, char *activity)
{
	pthread_mutex_lock(&data->print->mutex);
	if (is_ended(data))
	{
		pthread_mutex_unlock(&data->print->mutex);
		return ;
	}
	uptade_global_timer(data->gl_timer);
	printf("%d %d %s\n", data->gl_timer->timer, data->philo_x, activity);
	pthread_mutex_unlock(&data->print->mutex);
}

void	check_last_meal(t_data *data)
{
	if (is_ended(data))
		return ;
	update_local_timer(data->last_eat);
	if (data->last_eat->timer > data->args->time_to_die)
	{
		print_activity(data, DIED);
		pthread_mutex_lock(&data->is_finished->mutex);
		data->is_finished->var = 1;
		pthread_mutex_unlock(&data->is_finished->mutex);
	}
}
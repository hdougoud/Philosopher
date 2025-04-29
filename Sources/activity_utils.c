/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:07:15 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/29 13:51:53 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/struct.h"
#include "../include/thread.h"

int	is_ended(t_mutex *is_finished, t_mutex *satiated, t_args *args)
{
	int	status;

	status = 0;
	pthread_mutex_lock(&is_finished->mutex);
	if (is_finished->var == 1)
		status = 1;
	pthread_mutex_unlock(&is_finished->mutex);
	if (status == 1)
		return (status);
	pthread_mutex_lock(&satiated->mutex);
	if (satiated->var > 0)
	{
		if (args->must_eat >= satiated->var)
			satiated->var += 1;
		if (satiated->var > args->philosophers)
		{
			pthread_mutex_lock(&is_finished->mutex);
			is_finished->var = 1;
			pthread_mutex_unlock(&is_finished->mutex);
		}
		return (1);
	}
	pthread_mutex_unlock(&satiated->mutex);
	return (status);
}

void	print_activity(t_data *data, char *activity)
{
	pthread_mutex_lock(&data->print->mutex);
	if (is_ended(data->is_finished, data->satiated, data->args))
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
	if (is_ended(data->is_finished, data->satiated, data->args))
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
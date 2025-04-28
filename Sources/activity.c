/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:02:06 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/28 22:55:22 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/struct.h"
#include "../include/thread.h"

static void	action_thinking(t_data *data)
{
	if (data->action != THINK)
	{
		data->action = THINK;
		print_activity(data, IS_THINKING);
	}
	// while (1)  //repair here later
	// {
	// 	check_last_meal(data);
	// 	if (is_ended(data->is_finished))
	// 		return ;
	// 	pthread_mutex_lock(&data->fork->mutex);
	// 	if (data->fork->var >= 2)
	// 	{
	// 		pthread_mutex_unlock(&data->fork->mutex);
	// 		break ;
	// 	}
	// 	pthread_mutex_unlock(&data->fork->mutex);
	// 	usleep(1000);
	// }
}

static void	action_sleeping(t_data *data)
{
	data->action = SLEEP;
	print_activity(data, IS_SLEEPING);
	usleep(data->args->time_to_sleep * 1000); //change this for a periodic check
}

static void	action_eating(t_data *data)				//make a public array of all last_meal(possibly wrong : philosophers can't talk with other)
{
	check_last_meal(data);
	print_activity(data, IS_EATING);
	usleep(data->args->time_to_eat * 1000);
	reset_local_timer(data->last_eat);
	pthread_mutex_lock(&data->fork->mutex);
	data->fork->var += 2;
	data->owned_fork -= 2;
	pthread_mutex_unlock(&data->fork->mutex);
	action_sleeping(data);
}

static void	take_fork(t_data *data)
{
	pthread_mutex_lock(&data->fork->mutex);
	if (data->fork->var > 0)
	{
		data->fork->var -= 1;
		data->owned_fork += 1;
		print_activity(data, TAKEN_FORK);
	}
	pthread_mutex_unlock(&data->fork->mutex);
	if (data->owned_fork == 2)
		action_eating(data);
}

void	next_activity(t_data *data)
{
	while (1)
	{
		if (is_ended(data->is_finished))
			break ;
		take_fork(data);
		action_thinking(data);
	}
}
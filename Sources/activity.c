/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:02:06 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/02 13:48:38 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/struct.h"
#include "../include/thread.h"

static void	action_thinking(t_data *data)
{
	check_last_meal(data);
	if (is_ended(data))
		return;
	if (data->action != THINK)
	{
		data->action = THINK;
		print_activity(data, IS_THINKING);
	}
	usleep(1000);
}

static void	action_sleeping(t_data *data)
{
	if (is_ended(data))
		return ;
	gettimeofday(&data->nap_time, NULL);
	print_activity(data, IS_SLEEPING);
	usleep(data->args->time_to_sleep * 1000);
// 	while (data->nap_time->timer < data->args->time_to_sleep)
// 	{
// 		check_last_meal(data);
// 		if (is_ended(data))
// 			return;
// 		usleep(SLEEP_TIME);
// 		update_local_timer(data->nap_time); 
// 	}
}

static void	action_eating(t_data *data)
{
	check_last_meal(data);
	print_activity(data, IS_EATING);
	gettimeofday(&data->last_meal, NULL);
	usleep(data->args->time_to_eat * 1000);			//what if time_to_eat == 500 && time_to_die == 250 ?
	data->eated += 1;
}

static void	action_fork(t_data *data)
{
	pthread_mutex_t *first;
	pthread_mutex_t *second;
	
	if ((data->philo_x % 2) == 0)
	{
		first = data->right_hand;
		second = data->left_hand;
	}
	else
	{
		first = data->left_hand;
		second = data->right_hand;
	}
	pthread_mutex_lock(first);
	print_activity(data, TAKEN_FORK);
	pthread_mutex_lock(second);
	print_activity(data, TAKEN_FORK);
	action_eating(data);
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
	action_sleeping(data);
}

void	next_activity(t_data *data)
{
	while (1)
	{
		check_last_meal(data);
		action_fork(data);
		action_thinking(data);
		if (is_ended(data))
			break ;
	}
}
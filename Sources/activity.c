/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:02:06 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/07 22:11:10 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/struct.h"
#include "../include/thread.h"

static void	action_sleeping(t_philo *philo)
{
	int		timer;

	timer = 0;
	if (is_ended(data))
		return ;
	print_activity(data, IS_SLEEPING);
	if (gettimeofday(&data->nap_time, NULL))
		thread_error(data, "gettimeofday failed");
	while (timer < data->args->time_to_sleep)
	{
		usleep(1000);
		timer = update_local_timer(&data->nap_time);
		if (timer == -1)
			thread_error(data, "update timer failed");
		check_last_meal(data);
		if (is_ended(data))
			return ;
	}
}

static void	action_eating(t_philo *philo)
{
	int	timer;

	timer = 0;
	check_last_meal(data);
	print_activity(data, IS_EATING);
	data->eated += 1;
	gettimeofday(&data->last_meal, NULL);
	while (timer < data->args->time_to_eat)
	{
		usleep(1000);
		timer = update_local_timer(&data->last_meal);
		if (timer == -1)
			thread_error(data, "update timer failed");
		check_last_meal(data);
		if (is_ended(data))
			return ;
	}
}

static void	fork_availability(t_fork *fork, int action, t_philo *philo)
{
	if (is_ended(data))
		return ;
	while (1)
	{
		pthread_mutex_lock(fork->mutex);
		if (fork->used == 0 && action == LOCK)
		{
			fork->used = 1;
			pthread_mutex_unlock(fork->mutex);
			return;
		}
		else if (action == UNLOCK)
		{
			fork->used = 0;
			pthread_mutex_unlock(fork->mutex);
			return ;
		}
		pthread_mutex_unlock(fork->mutex);
		check_last_meal(data);
		if (is_ended(data))
			return ;
		usleep(1000);
	}
}

static void	action_fork(t_philo *philo)
{
	t_fork	*first;
	t_fork	*second;

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
	fork_availability(first, LOCK, data);
	print_activity(data, TAKEN_FORK);
	fork_availability(second, LOCK, data);
	print_activity(data, TAKEN_FORK);
	action_eating(data);
	fork_availability(first, UNLOCK, data);
	fork_availability(second, UNLOCK, data);
	action_sleeping(data);
}

void	next_activity(t_philo *philo)
{
	while (1)
	{
		check_last_meal(data);
		action_fork(data);
		print_activity(data, IS_THINKING);
		if (is_ended(data))
			break ;
	}
}

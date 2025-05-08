/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:02:06 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/08 10:55:37 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/struct.h"
#include "../include/thread.h"

static void	action_sleeping(t_philo *philo)
{
	int		timer;

	timer = 0;
	if (is_ended(philo))
		return ;
	print_activity(philo, IS_SLEEPING);
	if (gettimeofday(&philo->nap_time, NULL))
		thread_error(philo, "gettimeofday failed");
	while (timer < philo->data->time_to_sleep)
	{
		usleep(1000);
		///timer = update_local_timer(&data->nap_time);
		if (timer == -1)
			thread_error(philo, "update timer failed");
		//check_last_meal(data);
		if (is_ended(philo))
			return ;
	}
}

static void	action_eating(t_philo *philo)
{
	int	timer;

	timer = 0;
	//check_last_meal(data);
	print_activity(philo, IS_EATING);
	philo->meals += 1;
	//gettimeofday(&philo->last_meal, NULL);
	while (timer < philo->data->time_to_eat)
	{
		usleep(1000);
		//timer = update_local_timer(&data->last_meal);
		if (timer == -1)
			thread_error(philo, "update timer failed");
		//check_last_meal(data);
		if (is_ended(philo))
			return ;
	}
}

static void	action_fork(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if ((philo->id % 2) == 0)
	{
		first = &philo->right_hand;
		second = philo->left_hand;
	}
	else
	{
		first = philo->left_hand;
		second = &philo->right_hand;
	}
	pthread_mutex_lock(first);
	print_activity(philo, TAKEN_FORK);
	pthread_mutex_lock(second);
	print_activity(philo, TAKEN_FORK);
	action_eating(philo);
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
	action_sleeping(philo);
}

void	next_activity(t_philo *philo)
{
	while (1)
	{
		//check_last_meal(data);
		action_fork(philo);
		print_activity(philo, IS_THINKING);
		if (is_ended(philo))
			break ;
	}
}

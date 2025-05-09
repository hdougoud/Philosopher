/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:02:06 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/09 10:43:55 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/struct.h"
#include "../include/thread.h"

static void	action_sleeping(t_philo *philo)
{
	int				timer;
	struct timeval	new;

	timer = 0;
	if (is_ended(philo))
		return ;
	print_activity(philo, IS_SLEEPING);
	if (gettimeofday(&philo->nap_time, NULL))
		thread_error(philo, "gettimeofday failed");
	while (timer < philo->data->time_to_sleep)
	{
		usleep(1000);
		if (gettimeofday(&new, NULL))
			thread_error(philo, "gettimeofday failed");
		timer = (new.tv_sec - philo->nap_time.tv_sec) * 1000;
		timer += (new.tv_usec - philo->nap_time.tv_usec) / 1000;
		if (is_ended(philo))
			return ;
	}
}

static void	action_eating(t_philo *philo)
{
	int	timer;
	struct timeval	new;
	struct timeval	current;

	timer = 0;
	print_activity(philo, IS_EATING);
	pthread_mutex_lock(&philo->last_meal.mutex);
	if (gettimeofday(&philo->last_meal.tv, NULL))
	{
		pthread_mutex_unlock(&philo->last_meal.mutex);
		thread_error(philo, "gettimeofday failed");
	}
	current = philo->last_meal.tv;
	pthread_mutex_unlock(&philo->last_meal.mutex);
	philo->meals += 1;
	while (timer < philo->data->time_to_eat)
	{
		usleep(1000);
		if (gettimeofday(&new, NULL))
			thread_error(philo, "gettimeofday failed");
		timer = (new.tv_sec - current.tv_sec) * 1000;
		timer += (new.tv_usec - current.tv_usec) / 1000;
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

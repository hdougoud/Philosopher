/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:07:15 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/07 22:27:37 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/struct.h"
#include "../include/thread.h"

void	thread_error(t_philo *philo, char *str)
{
	if (is_ended(philo))
		return ;
	pthread_mutex_lock(&philo->data->print);
	putstr_fd(2, RED_ULTRA"Thread Error : ");
	putstr_fd(2, str);
	putstr_fd(2, YELLOW_ULTRA"\nExit program\n"RESET);
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_lock(&philo->data->death_check.mutex);
	philo->data->death_check.var = 1;
	pthread_mutex_unlock(&philo->data->death_check.mutex);
}

// static int	did_everyone_eat(t_philo *philo)
// {
// 	int	status;

// 	status = 0;
// 	if (philo->data->must_eat > 0)
// 	{
// 		pthread_mutex_lock(&philo->data->satiated.mutex);
// 		if (philo->meals == philo->data->must_eat)
// 		{
// 			philo->data->satiated.var += 1;
// 		}
// 		if (philo->satiated->var >= philo->args->philosophers)
// 		{
// 			philo->is_finished->var = 1;
// 			status = 1;
// 		}
// 		pthread_mutex_unlock(&philo->satiated.mutex);
// 	}
// 	return (status);
// }

int	is_ended(t_philo *philo)
{
	int	status;

	status = 0;
	pthread_mutex_lock(&philo->data->death_check.mutex);
	if (philo->data->death_check.var == 1)
		status = 1;
	if (status == 1)
	{
		pthread_mutex_unlock(&philo->data->death_check.mutex);
		return (status);
	}
	//status = did_everyone_eat(philo);
	pthread_mutex_unlock(&philo->data->death_check.mutex);
	return (status);
}

void	print_activity(t_philo *philo, char *activity)
{
	int				timer;
	struct timeval	temp;

	if (gettimeofday(&temp, NULL))
		thread_error(philo, "gettimeofday failed");
	timer = (temp.tv_usec - philo->timer->tv_usec) / 1000;
	timer += (temp.tv_sec - philo->timer->tv_sec) * 1000;
	pthread_mutex_lock(philo->print);
	if (!is_ended(philo))
		printf("%dms %d %s\n", timer, philo->philo_x, activity);
	pthread_mutex_unlock(philo->print);
}

void	check_last_meal(t_philo *philo)
{
	int	timer;

	if (is_ended(philo))
		return ;
	timer = update_local_timer(&philo->last_meal);
	if (timer > philo->args->time_to_die)
	{
		print_activity(philo, DIED);
		pthread_mutex_lock(&philo->is_finished->mutex);
		philo->is_finished->var = 1;
		pthread_mutex_unlock(&philo->is_finished->mutex);
	}
}

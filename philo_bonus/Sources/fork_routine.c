/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:11:29 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/06 14:17:13 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fork.h"
#include "../include/struct.h"

static void	is_satiated(t_data *data, t_fork *forks)
{
	if (!data->args->must_eat)
		return ;
	if (data->args->must_eat == forks->meal_count)
		exit(EXIT_SUCCESS);
	
}

static void	action_sleeping(t_data *data, t_fork *forks)
{
	int				elipsed;
	struct timeval	new;

	elipsed = 0;
	print_activity(data, forks, IS_SLEEPING);
	if (gettimeofday(&forks->last_nap, NULL))
		exit_fork("gettimeofday failed");
	while (elipsed < data->args->time_to_sleep)
	{
		usleep(1000);
		if (gettimeofday(&new, NULL))
			exit_fork("gettimeofday failed");
		elipsed = (new.tv_sec - forks->last_nap.tv_sec) * 1000;
		elipsed += (new.tv_usec - forks->last_nap.tv_usec) / 1000;
		check_last_meal(data, forks);
	}
}

static void	action_eating(t_data *data, t_fork *forks)
{
	int				elipsed;
	struct timeval	new;
	
	elipsed = 0;
	print_activity(data, forks, IS_EATING);
	forks->meal_count += 1;
	if (gettimeofday(&forks->last_meal, NULL))
		exit_fork("gettimeofday failed");
	while (elipsed < data->args->time_to_eat)
	{
		usleep(1000);
		if (gettimeofday(&new, NULL))
		{
			sem_post(data->fork);
			sem_post(data->fork);
			exit_fork("gettimeofday failed");
		}
		elipsed = (new.tv_sec - forks->last_meal.tv_sec) * 1000;
		elipsed += (new.tv_usec - forks->last_meal.tv_usec) / 1000;
		check_last_meal(data, forks);
	}
	is_satiated(data, forks);
}

static void	action_fork(t_data *data, t_fork *forks)
{
	sem_wait(data->fork);
	print_activity(data, forks, TAKEN_FORK);
	sem_wait(data->fork);
	print_activity(data, forks, TAKEN_FORK);
	action_eating(data, forks);
	sem_post(data->fork);
	sem_post(data->fork);
	action_sleeping(data, forks);
}

void	next_action(t_data *data, t_fork *forks)
{
	while (1)
	{
		check_last_meal(data, forks);
		action_fork(data, forks);
		check_last_meal(data, forks);
		print_activity(data, forks, IS_THINKING);
		usleep(1000);
	}
}
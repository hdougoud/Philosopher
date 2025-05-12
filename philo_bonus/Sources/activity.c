/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:36:11 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/12 12:03:03 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fork.h"
#include "../include/struct.h"

static void	action_eating(t_data *data, const int id)
{
	int				timer;
	struct timeval	temp;

	timer = 0;
	if (gettimeofday(&data->philo[id].last_meal, NULL))
		print_fork_error(data, "gettimeofday : function failed");
	while (timer < data->philosophers)
	{
		if (gettimeofday)
		timer = (temp.tv_usec - data->timer.tv_usec) / 1000;
		timer += (temp.tv_sec - data->timer.tv_sec) * 1000;
	}
}

static void	taking_fork(t_data *data, const int id)
{
	sem_wait(data->fork);
	print_activity(data, id, TAKEN_FORK);
	sem_wait(data->fork);
	print_activity(data, id, TAKEN_FORK);
	action_eating(data, id);
	sem_post(data->fork);
	sem_post(data->fork);
}

void	next_action(t_data *data, const int id)
{
	while(1)
	{
		taking_fork(data, id);
		usleep(10000);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:57:50 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/02 18:35:11 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/thread.h"
#include "../include/struct.h"

static int	(init_thread(t_data *data))
{
	int	status;

	status = 0;
	data->eated = 0;
	data->objective_complete = 0;
	if (gettimeofday(&data->last_meal, NULL))
		status = 1;
	if (gettimeofday(&data->nap_time, NULL))
		status = 1;
	if (status == 1)
		thread_error(data, "gettimeofday failed");
	return (status);
}

void	*exec_thread(void *thread)
{
	t_data	*data;

	data = (t_data *) thread;
	if (init_thread(data))
		return (NULL);
	if (data->args->philosophers == 1)
	{
		print_activity(data, TAKEN_FORK);
		usleep(data->args->time_to_die * 1000);
		print_activity(data, DIED);
		return (NULL);
	}
	if ((data->philo_x % 2) == 0)
		usleep(30);
	next_activity(data);
	return (NULL);
}

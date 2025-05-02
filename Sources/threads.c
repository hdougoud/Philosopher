/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:57:50 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/02 14:37:41 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/thread.h"
#include "../include/struct.h"

void	*exec_thread(void *thread)
{
	int		status;
	t_data	*data;

	status = 0;
	data = (t_data *) thread;
	if (gettimeofday(&data->last_meal, NULL))
		status = 1;
	if (gettimeofday(&data->nap_time, NULL))
		status = 1;
	if (status == 1)
	{
		pthread_mutex_lock(&data->is_finished->mutex);
		data->is_finished->var = 1;
		pthread_mutex_unlock(&data->is_finished->mutex);
		return (NULL);
	}
	//protection for signle philosopher
	data->action = NOTHING;
	data->eated = 0;
	data->objective_complete = 0;
	if ((data->philo_x % 2) == 0)
		usleep(30);
	next_activity(data);
	return (NULL);
}

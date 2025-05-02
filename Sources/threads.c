/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:57:50 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/02 10:50:01 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/thread.h"
#include "../include/struct.h"

void	*exec_thread(void *thread)
{
	t_data	*data;
	struct timeval	last_meal;
	struct timeval	nap_time;

	data = (t_data *) thread;
	if (gettimeofday(&last_meal, NULL))
		return (NULL);
	if (gettimeofday(&nap_time, NULL))
		return (NULL);
	data->last_meal = &last_meal;
	data->nap_time = &nap_time;
	data->action = NOTHING;
	data->eated = 0;
	data->objective_complete = 0;
	if ((data->philo_x % 2) == 0)
		usleep(30);
	next_activity(data);
	return (NULL);
}

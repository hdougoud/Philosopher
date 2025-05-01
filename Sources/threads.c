/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:57:50 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/30 23:17:37 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/thread.h"
#include "../include/struct.h"

void	*exec_thread(void *thread)
{
	t_data	*data;

	data = (t_data *) thread;
	data->nap_time = init_personnal_timer_struct();
	data->last_meal = init_personnal_timer_struct();
	data->action = NOTHING;
	data->owned_fork = 0;
	data->eated = 0;
	data->objective_complete = 0;
	if ((data->philo_x % 2) == 0)
		usleep(30);
	next_activity(data);
	return (NULL);
}

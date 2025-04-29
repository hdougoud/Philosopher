/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:57:50 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/29 19:00:36 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/thread.h"
#include "../include/struct.h"

void	*exec_thread(void *thread)
{
	t_data	*data;

	data = (t_data *) thread;
	data->last_action = init_personnal_timer_struct();
	data->last_eat = init_personnal_timer_struct();
	data->action = NOTHING;
	data->owned_fork = 0;
	data->eated = 0;
	data->objective_complete = 0;
	next_activity(data);
	return (NULL);
}

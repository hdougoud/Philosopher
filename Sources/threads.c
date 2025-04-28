/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:57:50 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/28 17:55:48 by hdougoud         ###   ########.fr       */
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
	next_activity(data);
	return (NULL);
}

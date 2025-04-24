/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:57:50 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/24 16:22:57 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include "../include/struct.h"

void	print_state(t_data *data)
{
	pthread_mutex_lock(&data->print->mutex);
	printf("states");
	pthread_mutex_unlock(&data->print->mutex);
}

void	*exec_thread(void *thread)
{
	t_data	*data;

	usleep(100000);
	data = (t_data *) thread;
	data->perso_timer = init_personnal_timer_struct();
	printf("Hello i'm a philosopher number %d\n", data->philo_x);
	return (NULL);
}

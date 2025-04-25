/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:57:50 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/25 18:52:40 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include "../include/struct.h"

int	check_last_meal(t_data *data)
{
	set_timer(&data->last_eat->tv, &data->last_eat->timer);
	if (data->last_eat->timer > data->args->time_to_die)
	{
		pthread_mutex_lock(&data->print->mutex);
		pthread_mutex_lock(&data->is_finished->mutex);
		printf("%d %d died", data->global_timer->timer, data->philo_x);
		data->is_finished->var = 1;
		pthread_mutex_unlock(&data->is_finished->mutex);
		pthread_mutex_unlock(&data->print->mutex);
		return (1);
	}
	return (0);
}

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
	data->last_action = init_personnal_timer_struct();
	data->last_eat = init_personnal_timer_struct();
	while (1)
	{
		pthread_mutex_lock(&data->is_finished->mutex);
		if (data->is_finished->var == 1)
			return (NULL);
		pthread_mutex_unlock(&data->is_finished->mutex);
	}
	printf("Hello i'm a philosopher number %d\n", data->philo_x);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:02:05 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/16 14:39:16 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_philosophers(t_data *data, int n_thread)
{
	int		i;
	pthread_t **thread;
	
	thread = ft_calloc(1, sizeof(pthread_t));
	if (!thread)
		print_error("Malloc : Allocation for **philo failed");
	i = 0;
	while (i < n_thread)
	{
		data->philo = malloc (sizeof(t_philo));
		data->philo->x_philo = i + 1;
		thread[i] = malloc(sizeof(t_philo)); //check leaks (free t_philo tab is possibly needed)
		if (!thread[i])
			print_error("Malloc : Allocation for philo[i] failed");
		if (pthread_create(thread[i], NULL, execute_philo, (void *)data))
			print_error("Pthread : Thread creation failed");
		i++;
	}
}

void	init_struct(t_data **data, int n_thread)
{
	data = NULL;

}

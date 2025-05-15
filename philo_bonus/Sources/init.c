/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:20:50 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/15 16:43:37 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../include/bonus.h"
#include "../include/struct.h"

static int	init_data_struct(t_data *data)
{
	int	max;

	sem_unlink("/sem_fork");
	sem_unlink("/sem_print");
	sem_unlink("/sem_death");
	max = data->philosophers;
	if (gettimeofday(&data->timer, NULL))
		return (1);
	data->fork = sem_open("/sem_fork", O_CREAT | O_EXCL, 0644, max);
	if (data->fork == SEM_FAILED)
		return (putstr_fd(2, RED"sem_fork open failed\n"RESET), 1);
	data->print = sem_open("/sem_print", O_CREAT | O_EXCL, 0644, 1);
	if (data->print == SEM_FAILED)
		return (putstr_fd(2, RED"sem_print open failed\n"RESET), 1);
	data->death_check = sem_open("/sem_death", O_CREAT | O_EXCL, 0644, max);
	if (data->death_check == SEM_FAILED)
		return (putstr_fd(2, RED"sem_death open failed\n"RESET), 1);
	return (0);
}

int	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	if (init_data_struct(data))
		return (1);
	while (i < data->philosophers)
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			return (print_error(data->print, "fork failed"));
		if (data->pid[i] == 0)
		{
			data->this_philo = data->all_philo[i];
			start_routine(data, i + 1);
		}
		else
			i++;
	}
	return (0);
}

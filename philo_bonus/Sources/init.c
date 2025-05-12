/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:20:50 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/12 12:43:47 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/wait.h>
#include "../include/bonus.h"
#include "../include/struct.h"


static int	wait_forks(t_data *data)
{
	int status;

	(void) data;
	waitpid(0, &status, 0);
	return (0);
}

static int	init_data_struct(t_data *data)
{
	int max_fork;

	max_fork = data->philosophers;
	sem_unlink("/sem_fork");
	sem_unlink("/sem_print");
	sem_unlink("/sem_satiated");
	sem_unlink("/sem_death_check");
	if (gettimeofday(&data->timer, NULL))
		return (1);
	data->fork = sem_open("/sem_fork", O_CREAT | O_EXCL, 0644, max_fork);
	if (data->fork == SEM_FAILED)
		return (putstr_fd(2, RED"sem_fork open failed\n"RESET), 1);
	data->print = sem_open("/sem_print", O_CREAT | O_EXCL, 0644, 1);
	if (data->print == SEM_FAILED)
		return (putstr_fd(2, RED"sem_print open failed\n"RESET), 1);
	data->satiated = sem_open("/sem_satiated", O_CREAT | O_EXCL, 0644, 1);
	if (data->satiated == SEM_FAILED)
		return (putstr_fd(2, RED"sem_satiated open failed\n"RESET), 1);
	data->death_check = sem_open("/sem_death_check", O_CREAT | O_EXCL, 0644, 1);
	if (data->satiated == SEM_FAILED)
		return (putstr_fd(2, RED"sem_death_check open failed\n"RESET), 1);
	return (0);
}

int	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	data->philo = ft_calloc(data->philosophers, sizeof(t_philo));
	if (!data->philo)
		return (1);
	if (init_data_struct(data))
		return (1);
	while (i < data->philosophers)
	{
		data->philo[i].pid = fork();
		if (data->philo[i].pid == -1)
			return (print_error(data->print, "fork failed"));
		if (data->philo[i].pid == 0)
			start_routine(data, i + 1);
		else
			i++;
	}
	wait_forks(data);
	return (0);
}

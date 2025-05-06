/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:41:29 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/05 18:36:43 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"
#include "../include/struct.h"

static int	init_sempahore(t_data *data, int n_philo)
{
	data->print = sem_open("/sem_print", O_CREAT | O_EXCL, 0644, 1);
	if (data->print == SEM_FAILED)
	{
		putstr_fd(2, RED"sem_print : open failed\n"YELLOW"Exit Program\n"RESET);
		return (1);
	}
	data->fork = sem_open("/sem_fork", O_CREAT | O_EXCL, 0644, n_philo);
	if (data->fork == SEM_FAILED)
	{
		putstr_fd(2, RED"sem_fork : open failed\n"YELLOW"Exit Program\n"RESET);
		return (1);
	}
	data->fork = sem_open("/sem_timer", O_CREAT | O_EXCL, 0644, 1);
	if (data->fork == SEM_FAILED)
	{
		putstr_fd(2, RED"sem_fork : open failed\n"YELLOW"Exit Program\n"RESET);
		return (1);
	}
	data->fork = sem_open("/sem_satiated", O_CREAT | O_EXCL, 0644, data->args->must_eat);
	if (data->fork == SEM_FAILED)
	{
		putstr_fd(2, RED"sem_fork : open failed\n"YELLOW"Exit Program\n"RESET);
		return (1);
	}
	return (0);
}

int	init_data(t_data *data, t_args *args)
{
	sem_unlink("/sem_fork");
	sem_unlink("/sem_print");
	sem_unlink("/sem_timer");
	sem_unlink("/sem_satiated");
	data->args = args;
	data->fork = NULL;
	data->print = NULL;
	data->timer = NULL;
	data->satiated = NULL;
	if (init_sempahore(data, args->philosophers))
		return (1);
	if (gettimeofday(&data->tv, NULL))
		return (1);
	return (0);
}

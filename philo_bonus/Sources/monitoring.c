/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:00:49 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/12 21:35:25 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/wait.h>
#include "../include/bonus.h"
#include "../include/struct.h"

static int	monitoring_check_death(t_data *data)
{
	int status;

	status = 0;
	sem_wait(data->death_check.sem);
	if (data->death_check.status == 1)
		status = 1;
	sem_post(data->death_check.sem);
	return (status);
}

static void	*satiety_monitoring(void *thread)
{
	int		i;
	t_data *data;

	i = 0;
	data = (t_data *)thread;
	while (i < data->philosophers)
	{
		sem_wait(data->satiated);
		if (monitoring_check_death(data))
			return (NULL);
		i++;
	}
	sem_wait(data->death_check.sem);
	data->death_check.status = 1;
	sem_post(data->death_check.sem);
	return (NULL);
}

int	monitoring(t_data *data)
{
	int			status;
	pthread_t	satiated;

	if (pthread_create(&satiated, NULL, satiety_monitoring, data))
	{
		print_error(data->print, "pthread : creation faield");
		return (free_all(data), 1);
	}
	waitpid(0, &status, 0);
	pthread_join(satiated, NULL);
	return (0);
}

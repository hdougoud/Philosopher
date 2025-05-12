/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:00:49 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/12 16:54:13 by hdougoud         ###   ########.fr       */
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

static void	*last_meal_monitoring(void *thread)
{
	int		i;
	int		timer;
	t_data	*data;
	struct timeval temp;

	i = 0;
	timer = 0;
	data = (t_data *)thread;
	while (timer < data->time_to_die)
	{
		if (i >= data->philosophers)
			i = 0;
		if (gettimeofday(&temp, NULL))
			return (print_error(data->print, "gettimeofday failed"), NULL);
		sem_wait(data->philo[i].last_meal.sem);
		timer = (temp.tv_usec - data->philo[i].last_meal.tv.tv_usec) / 1000;
		timer += (temp.tv_sec - data->philo[i].last_meal.tv.tv_sec) * 1000;
		sem_post(data->philo[i].last_meal.sem);
		if (monitoring_check_death(data))
			break ;
		i++;
	}
	print_activity(data, i, "died");
	sem_wait(data->death_check.sem);
	data->death_check.status = 1; //dosen't work
	sem_post(data->death_check.sem);
	return (NULL);
}

int	monitoring(t_data *data)
{
	int			i;
	int			status;
	pthread_t	meal;
	pthread_t	satiated;

	i = 0;
	if (pthread_create(&meal, NULL, last_meal_monitoring, data))
	{
		print_error(data->print, "pthread : creation faield");
		return (free_all(data), 1);
	}
	if (pthread_create(&satiated, NULL, satiety_monitoring, data))
	{
		print_error(data->print, "pthread : creation faield");
		return (free_all(data), 1);
	}
	putstr_fd(2, "wait started\n");
	waitpid(0, &status, 0);
	putstr_fd(2, "wait finiehd\n");
	while (i < data->philosophers)
	{
		kill(data->philo[i].pid, SIGTERM);
		putstr_fd(2, "KILLED");
		i++;
	}
	pthread_join(meal, NULL);
	pthread_join(satiated, NULL);
	return (0);
}

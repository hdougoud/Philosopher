/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:02:20 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/12 22:21:05 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "../include/fork.h"
#include "../include/struct.h"

static void *mealtime_monitoring(void *data)
{
	int				id;
	int				timer;
	struct timeval	temp;
	t_thread		*thread;
	
	thread = (t_thread *)data;
	timer = 0;
	id = thread->id;
	while (timer < thread->data->time_to_die)
	{
		usleep(1000);
		if (gettimeofday(&temp, NULL))
			return (print_fork_error(thread->data, "gettimeofday fail"), NULL);
		sem_wait(thread->data->philo[id].last_meal.sem);
		timer = (temp.tv_usec - thread->data->philo[id].last_meal.tv.tv_usec) / 1000;
		timer += (temp.tv_sec - thread->data->philo[id].last_meal.tv.tv_sec) * 1000;
		sem_post(thread->data->philo[id].last_meal.sem);
	}
	sem_post(thread->data->satiated);
	kill(thread->data->philo[id].pid, SIGTERM);
	return (NULL);
}

void	print_activity(t_data *data, const int id, const char *activity)
{
	int				timer;
	struct timeval	temp;

	if (gettimeofday(&temp, NULL))
		print_fork_error(data, "gettimeofday : function failed");
	timer = (temp.tv_usec - data->timer.tv_usec) / 1000;
	timer += (temp.tv_sec - data->timer.tv_sec) * 1000;
	sem_wait(data->print);
	printf("%dms %d %s\n", timer, id + 1, activity);
	sem_post(data->print);
}

void	print_fork_error(t_data *data, char *str)
{
	sem_wait(data->print);
	putstr_fd(2, RED"Error\n");
	putstr_fd(2, str);
	putstr_fd(2, YELLOW"Exit program"RESET);
	sem_post(data->print);
	sem_post(data->satiated);
	exit(EXIT_FAILURE);
}

void	start_routine(t_data *data, const int id)
{
	t_thread	thread;
	pthread_t 	monitoring;

	sem_wait(data->satiated);
	if ((id % 2) == 0)
		usleep(50);
	if (data->philosophers == 1)
	{
		print_activity(data, id, TAKEN_FORK);
		usleep(data->time_to_die * 1000);
		putstr_fd(2, "Exit");
		exit(EXIT_SUCCESS);
	}
	thread.id = id;
	thread.data = data;
	pthread_create(&monitoring, NULL, mealtime_monitoring, &thread);
	next_action(data, id);
	pthread_join(monitoring, NULL);
	sem_post(data->satiated);
	exit(EXIT_SUCCESS);
}

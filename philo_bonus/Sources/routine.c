/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:02:20 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/13 14:08:55 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fork.h"
#include "../include/struct.h"

void	clean_exit(t_data *data, const int id)
{
	int	i;

	i = 0;
	(void) id;
	usleep(1000);
	sem_close(data->fork);
	sem_close(data->print);
	sem_close(data->satiated);
	sem_close(data->death_check);
	while (i < data->philosophers)
	{
		sem_close(data->philo[id].end.sem);
		sem_close(data->philo[id].last_meal.sem);
		i++;
	}
	free(data->philo);
	exit(EXIT_SUCCESS);
}

void	check_the_end(t_data *data, const int id)
{
	int	status;

	status = 0;
	sem_wait(data->philo[id].end.sem);
	if (data->philo[id].end.status == 1)
		status = 1;
	sem_post(data->philo[id].end.sem);
	if (status == 1)
		clean_exit(data, id);
}

void	print_fork_error(t_data *data, const int id, char *str)
{
	sem_wait(data->print);
	putstr_fd(2, RED"Error\n");
	putstr_fd(2, str);
	putstr_fd(2, YELLOW"Exit program"RESET);
	sem_post(data->print);
	sem_post(data->satiated);
	clean_exit(data, id);
}

static void	*mealtime_monitoring(void *data)
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
			return (print_fork_error(thread->data, id, "fail get time"), NULL);
		sem_wait(thread->data->philo[id].last_meal.sem);
		timer = (temp.tv_usec - thread->data->philo[id].last_meal.tv.tv_usec) / 1000;
		timer += (temp.tv_sec - thread->data->philo[id].last_meal.tv.tv_sec) * 1000;
		sem_post(thread->data->philo[id].last_meal.sem);
	}
	print_activity(data, id, DIED);
	sem_wait(thread->data->philo[id].end.sem);
	thread->data->philo[id].end.status = 1;
	sem_post(thread->data->philo[id].end.sem);
	return (NULL);
}

void	start_routine(t_data *data, const int id)
{
	t_thread	thread;
	pthread_t 	monitoring;

	if ((id % 2) == 0)
		usleep(50);
	if (data->philosophers == 1)
	{
		print_activity(data, id, TAKEN_FORK);
		usleep(data->time_to_die * 1000);
		clean_exit(data, id);
	}
	thread.id = id;
	thread.data = data;
	pthread_create(&monitoring, NULL, mealtime_monitoring, &thread);
	pthread_detach(monitoring);
	next_action(data, id);
	clean_exit(data, id);
}

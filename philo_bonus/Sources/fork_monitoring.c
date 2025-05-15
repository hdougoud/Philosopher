/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_monitoring.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:53:14 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/15 17:00:22 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fork.h"
#include "../include/struct.h"

int	is_this_the_end(t_data *data)
{
	int	status;

	status = 0;
	sem_wait(data->this_philo.end.sem);
	if (data->this_philo.end.status == 1)
		status = 1;
	sem_post(data->this_philo.end.sem);
	return (status);
}

static void	*end_simulation(void *thread)
{
	t_data	*data;

	data = (t_data *)thread;
	usleep(500);
	sem_wait(data->death_check);
	sem_wait(data->this_philo.end.sem);
	data->this_philo.end.status = 1;
	sem_post(data->this_philo.end.sem);
	sem_post(data->death_check);
	return (NULL);
}

static void	*last_meal(void *thread)
{
	int				timer;
	t_data			*data;
	struct timeval	temp;

	timer = 0;
	data = (t_data *)thread;
	while (timer < data->time_to_die)
	{
		if (is_this_the_end(data))
			return (NULL);
		if (gettimeofday(&temp, NULL))
			return (print_fork_error(data, "gettimeofday failed"), NULL);
		sem_wait(data->this_philo.last_meal.sem);
		timer = (temp.tv_sec - data->this_philo.last_meal.tv.tv_sec) * 1000;
		timer += (temp.tv_usec - data->this_philo.last_meal.tv.tv_usec) / 1000;
		sem_post(data->this_philo.last_meal.sem);
		usleep(300);
	}
	print_activity(data, DIED);
	sem_wait(data->this_philo.end.sem);
	data->this_philo.end.status = 1;
	sem_post(data->this_philo.end.sem);
	return (NULL);
}

void	init_monitorings(t_data	*data)
{
	pthread_t	*meal;
	pthread_t	*end;

	meal = &data->this_philo.last_meal.thread;
	end = &data->this_philo.end.thread;
	if (pthread_create(meal, NULL, last_meal, data))
	{
		print_fork_error(data, "pthread_create : function failed");
		return ;
	}
	if (pthread_create(end, NULL, end_simulation, data))
	{
		print_fork_error(data, "pthread_create : function failed");
		return ;
	}
}

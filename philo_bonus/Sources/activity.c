/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:36:11 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/15 18:34:18 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fork.h"
#include "../include/struct.h"

void	print_activity(t_data *data, const char *activity)
{
	int				timer;
	struct timeval	temp;

	if (is_this_the_end(data))
		return ;
	if (gettimeofday(&temp, NULL))
		print_fork_error(data, "gettimeofday : function failed");
	timer = (temp.tv_usec - data->timer.tv_usec) / 1000;
	timer += (temp.tv_sec - data->timer.tv_sec) * 1000;
	sem_wait(data->print);
	printf("%d %d %s\n", timer, data->this_philo.id, activity);
	sem_post(data->print);
}

static void	action_sleeping(t_data *data)
{
	int				timer;
	struct timeval	temp;

	timer = 0;
	print_activity(data, IS_SLEEPING);
	if (gettimeofday(&data->this_philo.nap_time, NULL))
		print_fork_error(data, "gettimeofday : function failed");
	while (timer < data->time_to_sleep)
	{
		if (is_this_the_end(data))
			return ;
		if (gettimeofday(&temp, NULL))
			print_fork_error(data, "gettimeofday : function failed");
		timer = (temp.tv_usec - data->this_philo.nap_time.tv_usec) / 1000;
		timer += (temp.tv_sec - data->this_philo.nap_time.tv_sec) * 1000;
		usleep(200);
	}
}

static void	eat_loop(t_data	*data, struct timeval current)
{
	int				timer;
	struct timeval	temp;

	timer = 0;
	while (timer < data->time_to_eat)
	{
		if (is_this_the_end(data))
			return ;
		if (gettimeofday(&temp, NULL))
			print_fork_error(data, "gettimeofday : function failed");
		timer = (temp.tv_usec - current.tv_usec) / 1000;
		timer += (temp.tv_sec - current.tv_sec) * 1000;
		usleep(300);
	}
}

static void	action_eating(t_data *data)
{
	struct timeval	current;

	print_activity(data, IS_EATING);
	data->this_philo.meals += 1;
	if (data->must_eat > 0 && data->this_philo.meals > data->must_eat)
	{
		sem_post(data->fork);
		sem_post(data->fork);
		clean_exit(data);
	}
	sem_wait(data->this_philo.last_meal.sem);
	if (gettimeofday(&data->this_philo.last_meal.tv, NULL))
		print_fork_error(data, "gettimeofday : function failed");
	current = data->this_philo.last_meal.tv;
	sem_post(data->this_philo.last_meal.sem);
	eat_loop(data, current);
}

void	next_action(t_data *data)
{
	while (1)
	{
		sem_wait(data->fork);
		print_activity(data, TAKEN_FORK);
		sem_wait(data->fork);
		print_activity(data, TAKEN_FORK);
		action_eating(data);
		sem_post(data->fork);
		sem_post(data->fork);
		action_sleeping(data);
		print_activity(data, IS_THINKING);
		if (is_this_the_end(data))
			return ;
		usleep(200);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:36:11 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/13 23:59:30 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fork.h"
#include "../include/struct.h"

// void	print_activity(t_data *data, const int id, const char *activity)
// {
// 	int				timer;
// 	struct timeval	temp;

// 	if (gettimeofday(&temp, NULL))
// 		print_fork_error(data, id, "gettimeofday : function failed");
// 	timer = (temp.tv_usec - data->timer.tv_usec) / 1000;
// 	timer += (temp.tv_sec - data->timer.tv_sec) * 1000;
// 	sem_wait(data->print);
// 	printf("%dms %d %s\n", timer, id + 1, activity);
// 	sem_post(data->print);
// }

// static void	action_sleeping(t_data *data, const int id)
// {
// 	int				timer;
// 	struct timeval	temp;

// 	timer = 0;
// 	print_activity(data, id, IS_SLEEPING);
// 	if (gettimeofday(&data->philo[id].nap_time, NULL))
// 		print_fork_error(data, id, "gettimeofday : function failed");
// 	while (timer < data->time_to_sleep)
// 	{
// 		check_the_end(data, id);
// 		if (gettimeofday(&temp, NULL))
// 			print_fork_error(data, id, "gettimeofday : function failed");
// 		timer = (temp.tv_usec - data->philo[id].nap_time.tv_usec) / 1000;
// 		timer += (temp.tv_sec - data->philo[id].nap_time.tv_sec) * 1000;
// 		usleep(1000);
// 	}
// }

// static void	action_eating(t_data *data, const int id)
// {
// 	int				timer;
// 	struct timeval	temp;
// 	struct timeval	current;

// 	timer = 0;
// 	print_activity(data, id, IS_EATING);
// 	data->philo[id].meals += 1;
// 	if (data->must_eat > 1 && data->philo[id].meals >= data->must_eat)
// 		end_simulation(data, id);
// 	sem_wait(data->philo[id].last_meal.sem);
// 	if (gettimeofday(&data->philo[id].last_meal.tv, NULL))
// 		print_fork_error(data, id, "gettimeofday : function failed");
// 	current = data->philo[id].last_meal.tv;
// 	sem_post(data->philo[id].last_meal.sem);
// 	while (timer < data->time_to_eat)
// 	{
// 		check_the_end(data, id);
// 		if (gettimeofday(&temp, NULL))
// 			print_fork_error(data, id, "gettimeofday : function failed");
// 		timer = (temp.tv_usec - current.tv_usec) / 1000;
// 		timer += (temp.tv_sec - current.tv_sec) * 1000;
// 		usleep(1000);
// 	}
// }

// void	next_action(t_data *data, const int id)
// {
// 	while(1)
// 	{
// 		sem_wait(data->fork);
// 		print_activity(data, id, TAKEN_FORK);
// 		sem_wait(data->fork);
// 		print_activity(data, id, TAKEN_FORK);
// 		action_eating(data, id);
// 		sem_post(data->fork);
// 		sem_post(data->fork);
// 		check_the_end(data, id);
// 		action_sleeping(data, id);
// 		print_activity(data, id, IS_THINKING);
// 		check_the_end(data, id);
// 		usleep(1000);
// 	}
// }

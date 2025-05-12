/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:02:20 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/12 16:53:06 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fork.h"
#include "../include/struct.h"

void	check_end(t_data *data)
{
	sem_wait(data->death_check.sem);
	if (data->death_check.status == 1)
	{
		sem_post(data->death_check.sem);
		sem_post(data->satiated);
		exit(EXIT_SUCCESS);
	}
	sem_post(data->death_check.sem);
}

void	print_activity(t_data *data, const int id, const char *activity)
{
	int				timer;
	struct timeval	temp;

	if (gettimeofday(&temp, NULL))
		print_fork_error(data, "gettimeofday : function failed");
	timer = (temp.tv_usec - data->timer.tv_usec) / 1000;
	timer += (temp.tv_sec - data->timer.tv_sec) * 1000;
	check_end(data);
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
	sem_wait(data->satiated);
	if ((id % 2) == 0)
		usleep(50);
	next_action(data, id);
	if (data->philosophers == 1)
	{
		print_activity(data, id, TAKEN_FORK);
		usleep(data->time_to_die * 1000);
		putstr_fd(2, "Exit");
		exit(EXIT_SUCCESS);
	}
	sem_post(data->satiated);
	exit(EXIT_SUCCESS);
}

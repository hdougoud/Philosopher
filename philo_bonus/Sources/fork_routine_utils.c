/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_routine_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:20:27 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/06 13:57:07 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fork.h"
#include "../include/struct.h"

void	exit_fork(char *str)
{
	putstr_fd(2, RED"Error in fork : ");
	putstr_fd(2, str);
	putstr_fd(2, YELLOW"Exit Fork"RESET);
	exit(EXIT_FAILURE);
}

void	check_last_meal(t_data *data, t_fork *forks)
{
	int				elipsed;
	struct timeval	new;

	elipsed = 0;
	if (gettimeofday(&new, NULL))
		exit_fork("gettimeoofday failed");
	elipsed = (new.tv_sec - forks->last_meal.tv_sec) * 1000;
	elipsed += (new.tv_usec - forks->last_meal.tv_usec) / 1000;
	if (elipsed > data->args->time_to_die)
	{
		print_activity(data, forks, DIED);
		exit(EXIT_FAILURE);
	}
}

void	print_activity(t_data *data, t_fork *forks, char *activity)
{
	int				elipsed;
	struct timeval	new;

	elipsed = 0;
	sem_wait(data->print);
	if (gettimeofday(&new, NULL))
		exit_fork("gettimeofday failed");
	elipsed = (new.tv_sec - data->timer.tv_sec) * 1000;
	elipsed += (new.tv_usec - data->timer.tv_usec) / 1000;
	printf("%dms %d %s\n", elipsed, forks->philo_n, activity);
	sem_post(data->print);
}
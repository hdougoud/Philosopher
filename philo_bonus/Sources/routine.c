/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:02:20 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/12 11:55:35 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fork.h"
#include "../include/struct.h"

void	print_fork_error(t_data *data, char *str)
{
	sem_wait(data->print);
	putstr_fd(2, RED"Error\n");
	putstr_fd(2, str);
	putstr_fd(2, YELLOW"Exit program"RESET);
	sem_post(data->print);
	exit(EXIT_FAILURE);
}

static void	init_fork(t_data *data, const int id)
{
	data->philo[id].meals = 0;
	data->philo[id].satiated = 0;
	if (gettimeofday(&data->philo[id].last_meal, NULL))
		print_fork_error(data, "gettimeofday : function failed");
	if (gettimeofday(&data->philo[id].nap_time, NULL))
		print_fork_error(data, "gettimeofday : function failed");
}

void	start_routine(t_data *data, const int id)
{
	init_fork(data, id);
	if ((id % 2) == 0)
		usleep(5000);
	next_action(data, id);
	exit(EXIT_SUCCESS);
}

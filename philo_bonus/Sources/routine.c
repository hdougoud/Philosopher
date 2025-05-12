/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:02:20 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/12 15:02:03 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../include/fork.h"
#include "../include/struct.h"

void	print_fork_error(t_data *data, char *str, const int id)
{
	sem_wait(data->print);
	putstr_fd(2, RED"Error\n");
	putstr_fd(2, str);
	putstr_fd(2, YELLOW"Exit program"RESET);
	sem_post(data->print);
	sem_unlink(data->philo[id].last_meal.sem_name);
	exit(EXIT_FAILURE);
}

void	start_routine(t_data *data, const int id)
{
	sem_wait(data->satiated);
	if ((id % 2) == 0)
		usleep(50);
	next_action(data, id);
	sem_unlink(data->philo[id].last_meal.sem_name);
	exit(EXIT_SUCCESS);
}

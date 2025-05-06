/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:47:26 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/06 10:52:43 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fork.h"
#include "../include/struct.h"

static int	init_fork(t_fork *forks, int philo_n)
{
	forks->meal_count = 0;
	forks->philo_n = philo_n;
	if (gettimeofday(&forks->last_meal, NULL))
		return (1);
	if (gettimeofday(&forks->last_nap, NULL))
		return (1);
	return (0);
}

void	start_fork(t_data *data, int philo_n)
{
	t_fork	forks;
	
	(void) data;
	if (init_fork(&forks, philo_n))
		exit(EXIT_FAILURE);
	if ((philo_n % 2) == 0)
		usleep(50);
	print_activity(data, &forks, "test");
	usleep(100000);
	print_activity(data, &forks, "test2");
	exit(EXIT_SUCCESS);
}
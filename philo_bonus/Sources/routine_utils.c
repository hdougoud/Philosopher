/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:20:27 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/06 10:53:50 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fork.h"
#include "../include/struct.h"

void	print_activity(t_data *data, t_fork *forks, char *activity)
{
	int				elipsed;
	struct timeval	new;

	elipsed = 0;
	sem_wait(data->print);
	if (gettimeofday(&new, NULL))
	{
		putstr_fd(2, RED"gettimeofday failed"YELLOW"Exit program"RESET);
		exit(EXIT_FAILURE);
	}
	elipsed = (new.tv_sec - data->timer.tv_sec) * 1000;
	elipsed += (new.tv_usec - data->timer.tv_usec) / 1000;
	printf("%dms %d %s\n", elipsed, forks->philo_n, activity);
	sem_post(data->print);
}
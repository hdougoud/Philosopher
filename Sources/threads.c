/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:57:50 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/09 15:57:37 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/thread.h"
#include "../include/struct.h"

static int	(init_thread(t_philo *philo))
{
	philo->meals = 0;
	if (gettimeofday(&philo->nap_time, NULL))
		return (thread_error(philo, "gettimeofday failed"), 1);
	return (0);
}

void	*exec_thread(void *thread)
{
	t_philo	*philo;

	philo = (t_philo *)thread;
	if (init_thread(philo))
		return (NULL);
	if (philo->data->philosophers == 1)
	{
		print_activity(philo, TAKEN_FORK);
		usleep(philo->data->time_to_die * 1000);
		return (NULL);
	}
	if ((philo->id % 2) == 0)
		usleep(50);
	next_activity(philo);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:17:24 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/28 22:27:58 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include "../include/thread.h"
#include "../include/struct.h"

void	reset_local_timer(t_perso_timer *timer)
{
	update_local_timer(timer);
	timer->timer = 0;
}

t_perso_timer	*init_personnal_timer_struct(void)
{
	struct timeval	tv;
	t_perso_timer	*perso;

	if (gettimeofday(&tv, NULL))
		print_error("GetTimeOfDay : Unknow error");
	perso = malloc(sizeof(t_perso_timer));
	if (!perso)
		print_error("Malloc : Allocation failed");
	perso->timer = 0;
	perso->tv = tv;
	return (perso);
}

t_global_timer	*init_global_timer_struct(void)
{
	struct timeval	tv;
	t_global_timer	*time;

	time = malloc(sizeof(t_global_timer));
	if (!time)
		return (NULL);
	if (gettimeofday(&tv, NULL))
		return (NULL);
	if (pthread_mutex_init(&(time->mutex), NULL))
		print_error("Mutex : mutex failed");
	time->timer = 0;
	time->tv = tv;
	return (time);
}

int	update_local_timer(t_perso_timer *timer)
{
	int	old_sec;
	int	old_usec;

	old_sec = timer->tv.tv_sec;
	old_usec = timer->tv.tv_usec;
	if (gettimeofday(&timer->tv, NULL))
		return (1);
	timer->timer += (timer->tv.tv_sec - old_sec) * 1000;
	timer->timer += (timer->tv.tv_usec - old_usec) / 1000;
	return (0);
}

int	uptade_global_timer(t_global_timer *timer)
{
	int	old_sec;
	int	old_usec;

	pthread_mutex_lock(&timer->mutex);
	old_sec = timer->tv.tv_sec;
	old_usec = timer->tv.tv_usec;
	if (gettimeofday(&timer->tv, NULL))
		return (1);
	timer->timer += (timer->tv.tv_sec - old_sec) * 1000;
	timer->timer += (timer->tv.tv_usec - old_usec) / 1000;
	pthread_mutex_unlock(&timer->mutex);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:17:24 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/24 15:27:12 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include "../include/struct.h"

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

int	set_timer(struct timeval *tv, int *timer)
{
	int	old_sec;
	int	old_usec;
	int	new_timer;

	new_timer = *timer;
	old_sec = tv->tv_sec;
	old_usec = tv->tv_usec;
	if (gettimeofday(tv, NULL))
		return (1);
	new_timer += (tv->tv_sec - old_sec) * 1000;
	new_timer += (tv->tv_usec - old_usec) / 1000;
	*(timer) = new_timer;
	return (0);
}

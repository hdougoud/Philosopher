/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:17:24 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/17 19:21:04 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include "../include/struct.h"

t_time	*init_timer_struct(int *time, struct timeval *tv)
{
	//init struct here;
}

int set_timer(struct timeval *tv, int *timer)
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
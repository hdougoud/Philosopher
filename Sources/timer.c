/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:17:24 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/02 10:42:54 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include "../include/thread.h"
#include "../include/struct.h"

struct timeval	*init_global_timer(void)
{
	struct timeval	*tv;

	tv = malloc(sizeof(struct timeval));
	if (!tv)
		return (NULL);
	if (gettimeofday(tv, NULL))
		return (NULL);
	return (tv);
}

int	update_local_timer(struct timeval *timer)
{
	int				elipsed;
	struct timeval	new;

	if (gettimeofday(&new, NULL))
		return (-1);
	elipsed = (new.tv_sec - timer->tv_sec) * 1000;
	elipsed += (new.tv_usec - timer->tv_usec) / 1000;
	return (elipsed);
}

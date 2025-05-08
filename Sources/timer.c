/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:17:24 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/08 10:21:27 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include "../include/thread.h"
#include "../include/struct.h"

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

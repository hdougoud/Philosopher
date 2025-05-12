/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:36:11 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/12 11:55:19 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fork.h"
#include "../include/struct.h"

static void	taking_fork(t_data *data, const int id)
{
	sem_wait(data->fork);
	print_activity(data, id, TAKEN_FORK);
	sem_wait(data->fork);
	print_activity(data, id, TAKEN_FORK);
	sem_post(data->fork);
	sem_post(data->fork);
}

void	next_action(t_data *data, const int id)
{
	while(1)
	{
		taking_fork(data, id);
		usleep(10000);
	}
}
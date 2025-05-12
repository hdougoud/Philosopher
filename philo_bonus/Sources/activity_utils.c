/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:45:46 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/12 13:29:34 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fork.h"
#include "../include/struct.h"

void	print_activity(t_data *data, const int id, const char *activity)
{
	int				timer;
	struct timeval	temp;

	if (gettimeofday(&temp, NULL))
		print_fork_error(data, "gettimeofday : function failed", id);
	timer = (temp.tv_usec - data->timer.tv_usec) / 1000;
	timer += (temp.tv_sec - data->timer.tv_sec) * 1000;
	sem_wait(data->print);
	printf("%dms %d %s\n", timer, id, activity);
	sem_post(data->print);
}
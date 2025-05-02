/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:26:59 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/02 10:51:30 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include "../include/struct.h"

void	free_all(t_data **data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data[i]->is_finished->mutex);
	free(data[i]->is_finished);
	pthread_mutex_destroy(&data[i]->satiated->mutex);
	free(data[i]->satiated);
	free(data[i]->timer);
	pthread_mutex_destroy(data[i]->print);
	pthread_mutex_destroy(data[i]->right_hand);
	while (data[i])
	{
		free(data[i]);
		i++;
	}
	free(data);
}

int	join_all_thread(t_data **data, int n_threads)
{
	int	i;
	int	error_code;

	i = 0;
	while (i < n_threads)
	{
		error_code = pthread_join(data[i]->thread_id, NULL);
		if (error_code)
			print_error_code("pthread_join : ", error_code);
		i++;
	}
	return (0);
}

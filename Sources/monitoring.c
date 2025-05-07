/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:16:57 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/07 18:17:49 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include "../include/struct.h"
#include "../include/thread.h"

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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:26:59 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/24 15:24:24 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include "../include/struct.h"

// void	free_all(t_data **data)
// {
// 	int	i;

// 	i = 0;
// 	if (!data)
// 		return;
// 	while (data[i])
// 	{
//
// 	}
// }

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

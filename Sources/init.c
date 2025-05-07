/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:21:06 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/07 19:19:28 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include "../include/struct.h"

int	init_philosophers(t_data *data)
{
	data->philo = ft_calloc(data->philosophers, sizeof(t_philo));
	if (!data->philo)
		return (print_error("Malloc : allocation failed"));
	data->philo[0].thread_id = 0;
	printf("%d\n", data->philo->philo_x);
	return (0);
}

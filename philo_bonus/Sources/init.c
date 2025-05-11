/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:20:50 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/11 12:27:25 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bonus.h"
#include "../include/struct.h"

static int	init_philo_struct(t_data *data)
{
	
}

static int	init_data_struct(t_data *data)
{
	
}

int init_philosophers(t_data *data)
{
	data->philo = ft_calloc(data->philosophers, sizeof(t_philo));
	if (!data->philo)
		return (1);
	if (init_data_struct(data))
		return (1);
	if (init_philo_struct(data))
		return (1);
	return (0);
}
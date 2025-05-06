/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:05:13 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/06 09:54:14 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/struct.h"
#include "../include/philo_bonus.h"

void	close_all(t_data *data)
{
	if (data->fork || data->fork != SEM_FAILED)
	sem_close(data->fork);
	if (data->print || data->fork != SEM_FAILED)
	sem_unlink("/sem_fork");
	sem_unlink("/sem_print");
	sem_unlink("/sem_satiated");
}
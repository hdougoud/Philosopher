/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:41:29 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/05 13:31:28 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"
#include "../include/struct.h"

int	init_data(t_data *data, t_args *args)
{
	sem_unlink("/sem_fork");
	sem_unlink("/sem_print");
	data->args = args;
	data->fork = NULL;
	data->print = NULL;
	data->print = sem_open("/sem_print", O_CREAT, 0644, 1);
	if (data->print == SEM_FAILED)
	{
		putstr_fd(2, RED"sem_print : open failed"YELLOW"Exit Program"RESET);
		return (1);
	}
	data->fork = sem_open("/sem_fork", O_CREAT | O_EXCL, 0644, args->philosophers);
	if (data->fork == SEM_FAILED)
	{
		putstr_fd(2, RED"sem_fork : open failed"YELLOW"Exit Program"RESET);
		return (1);
	}
	return (0);
}

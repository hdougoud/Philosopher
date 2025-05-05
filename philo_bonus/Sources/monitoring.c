/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:36:40 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/05 13:49:26 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fork.h"
#include "../include/struct.h"

void	start_monitoring(t_data *data)
{
	pid_t *pid;

	pid = malloc(sizeof(pid_t) * data->args->philosophers);
	if (!pid)
	{
		putstr_fd(2, RED"Malloc PID failed"YELLOW"Exit Program"RESET);
		return ;
	}
	
	free(pid);
}
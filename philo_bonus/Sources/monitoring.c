/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:36:40 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/05 15:06:26 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fork.h"
#include "../include/struct.h"

void	wait_pids(pid_t *pid)
{
	int	i;
	int	status;

	i = 0;
	while (pid[i])
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
}

static void	launch_forks(pid_t *pids, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args->philosophers)
	{
		pids[i] = fork();
		if (pids[i] == 0)
			start_fork(data, i + 1);
		i++;
	}
}

void	start_monitoring(t_data *data)
{
	pid_t	*pids;

	pids = calloc(data->args->philosophers + 1, sizeof(pid_t));
	if (!pids)
	{
		putstr_fd(2, RED"Malloc PID failed\n"YELLOW"Exit Program\n"RESET);
		return ;
	}
	launch_forks(pids, data);
	wait_pids(pids);
	free(pids);
}
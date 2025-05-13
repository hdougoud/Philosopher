/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:00:49 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/13 14:07:35 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/wait.h>
#include "../include/bonus.h"
#include "../include/struct.h"

int	monitoring(t_data *data)
{
	//int			i;
	int			status;

	//i = 0;
	(void) data;
	waitpid(0, &status, 0);
	return (0);
}

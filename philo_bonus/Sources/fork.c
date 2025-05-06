/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:47:26 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/05 20:53:44 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fork.h"
#include "../include/struct.h"

void	start_fork(t_data *data, int philo_n)
{
	(void) data;
	printf("Hello im fork %d\n", philo_n);
	if ((philo_n % 2) == 0)
		usleep(10000);
	exit(EXIT_FAILURE);
}
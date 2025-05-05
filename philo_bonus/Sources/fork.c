/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:47:26 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/05 14:59:05 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fork.h"
#include "../include/struct.h"

void	start_fork(t_data *data, int philo_n)
{
	(void) data;
	printf("Hello im fork %d\n", philo_n);
	exit(EXIT_SUCCESS);
}
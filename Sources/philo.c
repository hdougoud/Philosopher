/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 00:18:54 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/15 21:25:56 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*execute_philo(void *pthread)
{
	t_philo	*philo;

	philo = (t_philo *)pthread;
	printf("Hello World");
	printf(" %d\n", philo->x_philo);
	return (NULL);
}

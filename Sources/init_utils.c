/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:06:21 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/07 18:15:45 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include "../include/struct.h"

pthread_mutex_t	*create_fork_tab(int total)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = ft_calloc(total + 1, sizeof(pthread_mutex_t));
	
	if (!forks)
		return (NULL);
	while (i < total)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			return (NULL);
		i++;
	}
	return (forks);
}

t_last_meal	**create_last_meal(int total)
{
	int i;
	t_last_meal **last_meal;

	last_meal = ft_calloc(total, sizeof(t_last_meal *));
	if (!last_meal)
		return (NULL);
	while(i < total)
	{
		last_meal[i] = calloc(1, sizeof(t_last_meal));
		if (last_meal[i])
			return (NULL);
		
	}
}

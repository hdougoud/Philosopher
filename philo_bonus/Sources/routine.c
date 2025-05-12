/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:02:20 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/12 13:29:12 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../include/fork.h"
#include "../include/struct.h"

void	print_fork_error(t_data *data, char *str, const int id)
{
	sem_wait(data->print);
	putstr_fd(2, RED"Error\n");
	putstr_fd(2, str);
	putstr_fd(2, YELLOW"Exit program"RESET);
	sem_post(data->print);
	sem_unlink(data->philo[id].last_meal.sem_name);
	exit(EXIT_FAILURE);
}

static char	*find_semname(const int id, char *sem_name, char *generic)
{
	int		i;
	int		j;
	char	nb[5];

	i = 0;
	j = 0;
	while (generic[i])
	{
		sem_name[i] = generic[i];
		i++;
	}
	ft_itoa(id, nb);
	while (nb[j])
	{
		sem_name[i++] = nb[j++];
	}
	sem_name[i] = '\0';
	return (sem_name);
}

static void	init_fork(t_data *data, const int id)
{
	find_semname(id, data->philo[id].last_meal.sem_name, "/sem_last_meal_");
	sem_unlink(data->philo[id].last_meal.sem_name);
	sem_open(data->philo[id].last_meal.sem_name, O_CREAT | O_EXCL, 0644, 1);
	data->philo[id].meals = 0;
	data->philo[id].satiated = 0;
	if (gettimeofday(&data->philo[id].last_meal.tv, NULL))
		print_fork_error(data, "gettimeofday : function failed", id);
	if (gettimeofday(&data->philo[id].nap_time, NULL))
		print_fork_error(data, "gettimeofday : function failed", id);
}

void	start_routine(t_data *data, const int id)
{
	init_fork(data, id);
	if ((id % 2) == 0)
		usleep(5000);
	next_action(data, id);
	sem_unlink(data->philo[id].last_meal.sem_name);
	exit(EXIT_SUCCESS);
}

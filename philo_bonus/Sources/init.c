/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:20:50 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/12 15:07:41 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../include/bonus.h"
#include "../include/struct.h"

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

static int	init_philo_struct(t_data *data)
{
	int	id;

	id = 0;
	while (id < data->philosophers)
	{
		find_semname(id, data->philo[id].last_meal.sem_name, "/sem_last_meal_");
		sem_unlink(data->philo[id].last_meal.sem_name);
		data->philo[id].last_meal.sem = sem_open(data->philo[id].last_meal.sem_name, O_CREAT | O_EXCL, 0644, 1);
		data->philo[id].meals = 0;
		if (gettimeofday(&data->philo[id].last_meal.tv, NULL))
			return (print_error(data->print, "gettimeofday : function failed"));
		if (gettimeofday(&data->philo[id].nap_time, NULL))
			return (print_error(data->print, "gettimeofday : function failed"));
	}
	return (0);
	}

static int	init_data_struct(t_data *data)
{
	int max;

	sem_unlink("/sem_fork");
	sem_unlink("/sem_print");
	sem_unlink("/sem_death");
	sem_unlink("/sem_satiated");
	max = data->philosophers;
	if (gettimeofday(&data->timer, NULL))
		return (1);
	data->fork = sem_open("/sem_fork", O_CREAT | O_EXCL, 0644, max);
	if (data->fork == SEM_FAILED)
		return (putstr_fd(2, RED"sem_fork open failed\n"RESET), 1);
	data->print = sem_open("/sem_print", O_CREAT | O_EXCL, 0644, 1);
	if (data->print == SEM_FAILED)
		return (putstr_fd(2, RED"sem_print open failed\n"RESET), 1);
	data->satiated = sem_open("/sem_satiated", O_CREAT | O_EXCL, 0644, max);
	if (data->satiated == SEM_FAILED)
		return (putstr_fd(2, RED"sem_satiated open failed\n"RESET), 1);
	data->death_check.sem = sem_open("/sem_death", O_CREAT | O_EXCL, 0644, 1);
	if (data->death_check.sem == SEM_FAILED)
		return (putstr_fd(2, RED"sem_death open failed\n"RESET), 1);
	return (0);
}

int	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	data->philo = ft_calloc(data->philosophers, sizeof(t_philo));
	if (!data->philo)
		return (1);
	if (init_data_struct(data))
		return (1);
	if (init_philo_struct(data))
		return (0);
	while (i < data->philosophers)
	{
		data->philo[i].pid = fork();
		if (data->philo[i].pid == -1)
			return (print_error(data->print, "fork failed"));
		if (data->philo[i].pid == 0)
			start_routine(data, i + 1); //remove +1 later
		else
			i++;
	}
	return (0);
}

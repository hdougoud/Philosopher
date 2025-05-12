/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:58:48 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/12 15:50:29 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bonus.h"
#include "../include/struct.h"

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	sem_close(data->fork);
	sem_close(data->print);
	sem_close(data->satiated);
	sem_close(data->death_check.sem);
	while (i < data->philosophers)
	{
		sem_close(data->philo[i].last_meal.sem);
		sem_unlink(data->philo[i].last_meal.sem_name);
	}
	sem_unlink("/sem_fork");
	sem_unlink("/sem_print");
	sem_unlink("/sem_death");
	sem_unlink("/sem_satiated");
	free(data->philo);
}

static int	convert_numbers(t_data *data, int argc, char **argv)
{
	data->philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->must_eat = 0;
	if (data->philosophers == -1 || data->time_to_die == -1
		|| data->time_to_eat == -1 || data->time_to_sleep == -1)
		return (putstr_fd(2, YELLOW"Exit Program\n"RESET), 1);
	if (argc == 6)
	{
		data->must_eat = ft_atoi(argv[5]);
		if (data->must_eat == -1)
			return (putstr_fd(2, YELLOW"Exit Program\n"RESET), 1);
	}
	if (data->philosophers < 1)
	{
		putstr_fd(2, RED"Not enough philosophers\n"RESET);
		return (putstr_fd(2, YELLOW"Exit program\n"RESET), 1);
	}
	if (data->philosophers > 200)
	{
		putstr_fd(2, RED"Too much philosophers\n"RESET);
		return (putstr_fd(2, YELLOW"Exit program\n"RESET), 1);
	}
	return (0);
}

static int	check_args(int argc)
{
	if (argc < 5)
	{
		putstr_fd(2, RED"Not enough args\n"YELLOW"Exit Program\n"RESET);
		return (1);
	}
	if (argc > 6)
	{
		putstr_fd(2, RED"Too much args\n"YELLOW"Exit Program\n"RESET);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc))
		return (1);
	if (convert_numbers(&data, argc, argv))
		return (1);
	if (init_philosophers(&data))
		return (1);
	if (monitoring(&data))
		return (1);
	free_all(&data);
}

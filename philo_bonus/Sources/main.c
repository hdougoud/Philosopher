/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:58:48 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/10 19:15:35 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bonus.h"
#include "../include/struct.h"

static void	free_all(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->satiated.mutex);
	pthread_mutex_destroy(&data->death_check.mutex);
	while (i >= data->philosophers)
	{
		pthread_mutex_destroy(&data->philo[i].right_hand);
		pthread_mutex_destroy(&data->philo[i].last_meal.mutex);
		i++;
	}
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
		return (print_error(&data->print, "Not enough philosophers"));
	if (data->philosophers > 200)
		return (print_error(&data->print, "Too much philosophers"));
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
}

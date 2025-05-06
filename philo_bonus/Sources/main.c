/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:20:58 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/06 15:19:32 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/struct.h"
#include "../include/philo_bonus.h"

static int	convert_numbers(t_args *args, int argc, char **argv)
{
	args->philosophers = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->must_eat = 0;
	if (args->philosophers == -1 || args->time_to_die == -1
		|| args->time_to_eat == -1 || args->time_to_sleep == -1)
		return (putstr_fd(2, YELLOW"Exit Program\n"RESET), 1);
	if (argc == 6)
	{
		args->must_eat = ft_atoi(argv[5]);
		if (args->must_eat == -1)
			return (putstr_fd(2, YELLOW"Exit Program\n"RESET), 1);
	}
	if (args->philosophers < 1)
	{
		putstr_fd(2, RED"Not enough philosophers\n"YELLOW"Exit Program\n"RESET);
		return (1);
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
	t_args	args;
	t_data	data;
	
	if (check_args(argc))
		return (1);
	if (convert_numbers(&args, argc, argv))
		return (1);
	if (init_data(&data, &args))
		return ((close_all(&data)), 1);
	start_monitoring(&data);
	close_all(&data);
}
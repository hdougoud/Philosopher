/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:23:47 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/06 15:00:30 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include "../include/struct.h"

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
	t_args		args;
	t_data		**data;
	t_global	*global;

	data = NULL;
	if (check_args(argc))
		return (1);
	if (convert_numbers(&args, argc, argv))
		return (1);
	init_philosophers(&data, &args, &global, args.philosophers);
	join_all_thread(data, args.philosophers);
	if (data[0]->objective_complete == 1)
		printf(GREEN_ULTRA"Simulation complete\n"RESET);
	else
		printf(RED_ULTRA"A philosopher is dead\n"RESET);
	free_all(data, global);
	return (0);
}

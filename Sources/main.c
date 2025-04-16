/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:23:47 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/16 14:39:39 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	convert_numbers(t_args *args, int argc, char **argv)
{
	args->philosophers = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->must_eat = ft_atoi(argv[5]);
	if (args->philosophers < 1)
		print_error("Not enough philosophers");
	if (args->philosophers > PTHREAD_THREADS_MAX) //disable this later en check if the thread function failed with big ammount
		print_error("Too much philosophers");
}

static void	check_args(int argc)
{
	if (argc < 5)
		print_error("Not enough args");
	if (argc > 6)
		print_error("Too much args");
}

int	main(int argc, char **argv)
{
	t_data	**data;
	t_args	*args;
							//make a array with data strcut and give a copy to all thread!
	data = NULL;
	args = NULL;
	check_args(argc);
	init_struct(data);
	convert_numbers(args, argc, argv);
	init_philosophers(&data, args->philosophers);
	printf("philosophers	%d\n", args->philosophers);
	printf("time_to_die	%d\n", args->time_to_die);
	printf("time_to_eat	%d\n", args->time_to_eat);
	printf("time_to_sleep	%d\n", args->time_to_sleep);
	printf("must_eat	%d\n", args->must_eat);
	return (0);
}

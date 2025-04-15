/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:23:47 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/15 17:26:37 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	convert_numbers(t_data *data, int argc, char **argv)
{
	data->n_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	if (data->n_philosophers < 1)
		print_error("Not enough philosophers");
	if (data->n_philosophers > PTHREAD_THREADS_MAX) //disable this later en check if the thread function failed with big ammount
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
	t_data	data;

	check_args(argc);
	init_struct(&data);
	convert_numbers(&data, argc, argv);
	init_philosophers(&data, data.n_philosophers);
	printf("philosophers	%d\n", data.n_philosophers);
	printf("time_to_die	%d\n", data.time_to_die);
	printf("time_to_eat	%d\n", data.time_to_eat);
	printf("time_to_sleep	%d\n", data.time_to_sleep);
	printf("must_eat	%d\n", data.must_eat);
	return (0);
}

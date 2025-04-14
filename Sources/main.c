/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:23:47 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/14 10:48:49 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	convert_numbers(t_philo *philo, char **argv)
{
	philo->philosophers = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->must_eat = ft_atoi(argv[5]);
	philo->threads = philo->philosophers;
	if (philo->philosophers < 1)
		print_error("Not enough philosophers");
	if (philo->philosophers > PTHREAD_THREADS_MAX) //disable this later en check if the thread function failed with big ammount
		print_error("Too much philosophers");
}

static void	check_args(int argc)
{
	if (argc < 6)
		print_error("Not enough args");
	if (argc > 6)
		print_error("Too much args");
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	check_args(argc);
	convert_numbers(&philo, argv);
	printf("philosophers	%d\n", philo.philosophers);
	printf("time_to_die	%d\n", philo.time_to_die);
	printf("time_to_eat	%d\n", philo.time_to_eat);
	printf("time_to_sleep	%d\n", philo.time_to_sleep);
	printf("must_eat	%d\n", philo.must_eat);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:23:47 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/17 19:21:10 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include "../include/struct.h"

static void	*exec_thread(void *thread)
{
	t_data	*data;
	
	data = (t_data *) thread;
	printf("Hello i'm a philosopher number %d\n", data->philo_x);
	set_timer();
	return (NULL); 
}

static void	init_philosophers(t_data **data, t_args *args, int n_thread)
{
	int		i;

	(void) args;
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		print_error("Malloc : Allocation for **philo failed");
	i = 0;
	while (i < n_thread)
	{
		data[i] = malloc(sizeof(t_data)); //check leaks (free t_philo tab is possibly needed)
		if (!data[i])
			print_error("Malloc : Allocation for philo[i] failed");
		data[i]->philo_x = i + 1;
		if (pthread_create(&data[i]->thread_id, NULL, exec_thread, (void *)data[i]))
			print_error("Pthread : Thread creation failed");
		i++;
	}
}

int set_timer(struct timeval *tv, int *timer)
{
	int	old_sec;
	int	old_usec;
	int	new_timer;

	new_timer = *timer;
	old_sec = tv->tv_sec;
	old_usec = tv->tv_usec;
	if (gettimeofday(tv, NULL))
		return (1);
	new_timer += (tv->tv_sec - old_sec) * 1000;
	new_timer += (tv->tv_usec - old_usec) / 1000;
	*(timer) = new_timer;
	return (0);
}

static void	convert_numbers(t_args *args, int argc, char **argv)
{
	args->philosophers = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->must_eat = 0;
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
	int		timer;
	t_data	**data;
	t_args	args;
	struct	timeval tv;
							//make a array with data strcut and give a copy to all thread!
	timer = 0;
	data = NULL;
	check_args(argc);
	convert_numbers(&args, argc, argv);
	if (gettimeofday(&tv, NULL))
		return (1);
	printf("%d\n", timer);
	init_philosophers(data, &args, timer, tv);
	// printf("philosophers	%d\n", args.philosophers);
	// printf("time_to_die	%d\n", args.time_to_die);
	// printf("time_to_eat	%d\n", args.time_to_eat);
	// printf("time_to_sleep	%d\n", args.time_to_sleep);
	// printf("must_eat	%d\n", args.must_eat);
	usleep(1000);
	return (0);
}

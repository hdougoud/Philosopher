/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:23:47 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/24 11:32:54 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include "../include/struct.h"

static void	*exec_thread(void *thread)
{
	t_data	*data;
	
	data = (t_data *) thread;
	printf("Hello i'm a philosopher number %d\n", data->philo_x);
	pthread_mutex_lock(&data->global_timer->mutex);
	usleep(25000);
	data->perso_timer = init_personnal_timer_struct();
	usleep(25000);
	set_timer(&data->global_timer->tv, &data->global_timer->timer);
	printf("Global timer is at %dms\n", data->global_timer->timer);
	set_timer(&data->perso_timer->tv, &data->perso_timer->timer);
	printf("Personal timer is at %dms\n", data->perso_timer->timer);
	pthread_mutex_unlock(&data->global_timer->mutex);
	return (NULL); 
}

static void	init_philosophers(t_data ***data, t_args *args)
{
	int				i;
	int				n_thread;
	int				error_code;
	t_global_timer	*gl_timer;

	n_thread = args->philosophers;
	*data = ft_calloc(n_thread, sizeof(t_data *));
	if (!*data)
		print_error("Malloc : Allocation for **philo failed");
	i = 0;
	gl_timer = init_global_timer_struct();//checkmalloc
	while (i < n_thread)
	{
		(*data)[i] = malloc(sizeof(t_data));
		if (!(*data)[i])
			print_error("Malloc : Allocation for philo[i] failed");
		(*data)[i]->philo_x = i + 1;
		(*data)[i]->global_timer = gl_timer;
		error_code = pthread_create(&(*data)[i]->thread_id, NULL, exec_thread, (void *)(*data)[i]);
		if (error_code)
			print_error_code("Pthread failed : ", error_code);
		usleep(100);
		i++;
	}
}

static int	convert_numbers(t_args *args, int argc, char **argv)
{
	args->philosophers = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->must_eat = 0;
	if (args->philosophers == -1 || args->time_to_die == - 1 ||
		args->time_to_eat == -1 || args->time_to_sleep == -1)
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
	t_data	**data;
	t_args	args;

	data = NULL;
	if (check_args(argc))
		return (1);
	if (convert_numbers(&args, argc, argv))
		return (1);
	init_philosophers(&data, &args);
	usleep(1000000);
	return (0);
}

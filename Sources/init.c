/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:43:21 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/07 17:30:59 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include "../include/struct.h"

static int	init_mutex(t_mutex **mutex)
{
	int	error;

	error = 0;
	*mutex = malloc(sizeof(t_mutex));
	if (!*mutex)
		return (print_error("Malloc : Allocation faield"), 1);
	error = pthread_mutex_init(&(*mutex)->mutex, NULL);
	if (error)
	{
		free(*mutex);
		*mutex = NULL;
		return (print_error_code("pthread create : ", error), 1);
	}
	(*mutex)->var = 0;
	return (0);
}

static pthread_mutex_t	*create_fork_tab(int total)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = calloc(total + 1, sizeof(pthread_mutex_t));
	if (!forks)
		return (NULL);
	while (i < total)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			return (NULL);
		i++;
	}
	return (forks);
}

static t_global	*init_global_struct(t_args *args)
{
	t_global	*global;

	global = ft_calloc(1, sizeof(t_global));
	if (!global)
		return (NULL);
	global->tv = init_global_timer();
	if (!global->tv)
		return (free_global_struct(global), NULL);
	if (init_mutex(&global->is_finished))
		return (free_global_struct(global), NULL);
	if (init_mutex(&global->satiated))
		return (free_global_struct(global), NULL);
	if (pthread_mutex_init(&global->print, NULL))
		return (free_global_struct(global), NULL);
	global->fork = create_fork_tab(args->philosophers);
	if (!global->fork)
		return (free_global_struct(global), NULL);
	global->args = args;
	return (global);
}

static int	apply_global_struct(t_data *data, t_global *global, int i)
{
	data->right_hand = malloc(sizeof(t_fork));
	if (!data->right_hand)
		return (1);
	data->left_hand = malloc(sizeof(t_fork));
	if (!data->left_hand)
		return (1);
	data->philo_x = i + 1;
	data->args = global->args;
	data->print = &global->print;
	data->timer = global->tv;
	data->satiated = global->satiated;
	data->is_finished = global->is_finished;
	data->right_hand->mutex = &global->fork[i];
	data->left_hand->mutex = &global->fork[(i + 1) % global->args->philosophers];
	data->right_hand->used = 0;
	data->left_hand->used = 0;
	return (0);
}

int	init_philosophers(t_data ***data, t_args *args, t_global **gl, int n_thread)
{
	int	i;
	int	error_code;

	(*gl) = init_global_struct(args);
	if (!*gl)
		return (1);
	*data = ft_calloc(n_thread + 1, sizeof(t_data *));
	if (!*data)
		print_error("Malloc : Allocation for **philo failed");
	i = 0;
	while (i < n_thread)
	{
		(*data)[i] = ft_calloc(1, sizeof(t_data));
		if (!(*data)[i])
			print_error("Malloc : Allocation for philo[i] failed");
		if (apply_global_struct((*data)[i], *gl, i))
			return (1);
		error_code = pthread_create(&(*data)[i]->thread_id, NULL,
				exec_thread, (void *)(*data)[i]);
		if (error_code)
			print_error_code("Pthread failed : ", error_code);
		i++;
	}
	return (0);
}

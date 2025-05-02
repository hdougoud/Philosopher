/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:43:21 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/02 14:22:12 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include "../include/struct.h"

static int	init_mutex(t_mutex **mutex)
{
	*mutex = malloc(sizeof(t_mutex));
	if (!*mutex)
		return (1); //print malloc error
	if (pthread_mutex_init(&(*mutex)->mutex, NULL))
		return (1); //print error code
	(*mutex)->var = 0;
	return (0);
}

static pthread_mutex_t	*create_fork_tab(int total)
{
	int	i;
	pthread_mutex_t *forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * total);
	if (!forks)
		return (NULL);
	while(i < total)
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

	global = malloc(sizeof(t_global));
	if (!global)
		return (NULL);
	global->tv = NULL;
	global->fork = NULL;
	global->satiated = NULL;
	global->is_finished = NULL;
	global->tv = init_global_timer();
	if (!global->tv)
		return (NULL);
	if (init_mutex(&global->is_finished))
		return (NULL);
	if (init_mutex(&global->satiated))
		return (NULL);
	if (pthread_mutex_init(&global->print, NULL))
		return (NULL);
	global->fork = create_fork_tab(args->philosophers);
	if (!global->fork)
		return (NULL);
	global->args = args;
	return (global);
}

static void	apply_global_struct(t_data *data, t_global *global, int i)
{
	data->philo_x = i + 1;
	data->args = global->args;
	data->print = &global->print;
	data->timer = global->tv;
	data->satiated = global->satiated;
	data->is_finished = global->is_finished;
	data->right_hand = &global->fork[i];
	data->left_hand = &global->fork[(i + 1) % global->args->philosophers];
}

int	init_philosophers(t_data ***data, t_args *args, t_global **global, int n_thread)
{
	int	i;
	int	error_code;

	(*global) = init_global_struct(args);
	if (!*global)
		return (1);
	*data = ft_calloc(n_thread + 1, sizeof(t_data *));
	if (!*data)
		print_error("Malloc : Allocation for **philo failed");
	i = 0;
	while (i < n_thread)
	{
		(*data)[i] = malloc(sizeof(t_data));
		if (!(*data)[i])
			print_error("Malloc : Allocation for philo[i] failed");
		apply_global_struct((*data)[i], *global, i);
		error_code = pthread_create(&(*data)[i]->thread_id, NULL, \
	exec_thread, (void *)(*data)[i]);
		if (error_code)
			print_error_code("Pthread failed : ", error_code);
		i++;
	}
	return (0);
}

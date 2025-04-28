/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:43:21 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/27 21:15:08 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include "../include/struct.h"

static int	init_global_struct(t_global *global, t_args *args)
{
	global->timer = init_global_timer_struct();
	if (!global->timer)
		return (1);
	global->fork = malloc(sizeof(t_mutex));
	if (!global->fork)
		return (1);
	if (pthread_mutex_init(&global->fork->mutex, NULL))
		return (1); //print error code
	global->is_finished = malloc(sizeof(t_mutex));
	if (!global->is_finished)
		return (1);
	if (pthread_mutex_init(&global->is_finished->mutex, NULL))
		return (1); //print error code
	global->print = malloc(sizeof(t_print));
	if (!global->print)
		return (1);
	if (pthread_mutex_init(&global->print->mutex, NULL))
		return(1);
	global->fork->var = args->philosophers;
	global->is_finished->var = 0;
	global->args = args;
	return (0);
}

static void	apply_global_struct(t_data *data, t_global *global, int i)
{
	data->philo_x = i + 1;
	data->args = global->args;
	data->gl_timer = global->timer;
	data->fork = global->fork;
	data->is_finished = global->is_finished;
	data->print = global->print;
}

int	init_philosophers(t_data ***data, t_args *args)
{
	int			i;
	int			n_thread;
	int			error_code;
	t_global	global;

	if (init_global_struct(&global, args))
		return (1);
	n_thread = args->philosophers;
	*data = ft_calloc(n_thread, sizeof(t_data *));
	if (!*data)
		print_error("Malloc : Allocation for **philo failed");
	i = 0;
	while (i < n_thread)
	{
		(*data)[i] = malloc(sizeof(t_data));
		if (!(*data)[i])
			print_error("Malloc : Allocation for philo[i] failed");
		apply_global_struct((*data)[i], &global, i);
		error_code = pthread_create(&(*data)[i]->thread_id, NULL, \
		exec_thread, (void *)(*data)[i]);
		if (error_code)
			print_error_code("Pthread failed : ", error_code);
		i++;
	}
	return (0);
}

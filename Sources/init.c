/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:43:21 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/30 17:02:16 by hdougoud         ###   ########.fr       */
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

static t_mutex	**create_fork_tab(int total)
{
	int	i;
	t_mutex **forks;

	forks = malloc(sizeof(int *) * total + 1);
	if (!forks)
		return (NULL);
	while(i < total)
	{
		if (init_mutex(&forks[i]))
			return (NULL);
		i++; //when we alocate a fork to a data[i], alocate n philo - 1 to the left
	}
	return (forks);
}

static int	init_global_struct(t_global *global, t_args *args)
{
	global->timer = NULL;
	global->is_finished = NULL;
	global->print = NULL;
	global->satiated = NULL;
	global->timer = init_global_timer_struct();
	if (!global->timer)
		return (1);
	if (init_mutex(&global->is_finished))
		return (1);
	if (init_mutex(&global->satiated))
		return (1);
	global->print = malloc(sizeof(t_print));
	if (!global->print)
		return (1);
	if (pthread_mutex_init(&global->print->mutex, NULL))
		return(1);
	global->args = args;
	global->fork = create_fork_tab(args->philosophers);
	if (!global->fork)
		return (1);
	return (0);
}

static void	apply_global_struct(t_data *data, t_global *global, int i)
{
	data->philo_x = i + 1;
	data->args = global->args;
	data->print = global->print;
	data->gl_timer = global->timer;
	data->satiated = global->satiated;
	data->is_finished = global->is_finished;
}

int	init_philosophers(t_data ***data, t_args *args, int n_thread)
{
	int			i;
	int			error_code;
	t_global	global;

	if (init_global_struct(&global, args))
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
		apply_global_struct((*data)[i], &global, i);
		error_code = pthread_create(&(*data)[i]->thread_id, NULL, \
	exec_thread, (void *)(*data)[i]);
		if (error_code)
			print_error_code("Pthread failed : ", error_code);
		i++;
	}
	return (0);
}

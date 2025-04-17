/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:28:05 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/17 19:17:04 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <pthread.h>

typedef enum e_action
{
	EAT = 1,
	SLEEP = 2,
	THINK = 3
}	t_action;

typedef struct s_mutex
{
	pthread_mutex_t	mutex;
	int				*var;
}	t_mutex;

typedef struct s_args
{
	int		philosophers;
	int		time_to_eat;
	int		time_to_die;
	int		time_to_sleep;
	int		must_eat;
}	t_args;

typedef struct s_time
{
	pthread_mutex_t	mutex;
	int				*time;
	struct timeval	*tv;
}	t_time;

typedef struct s_data
{
	pthread_t	thread_id;
	int			philo_x;
	int			current_action;
	int			last_eat;
	t_action	action;
	t_time		*time;
	t_args		*args;
	t_mutex		*fork;
	t_mutex		*timer;
	t_mutex		*is_finished;
}	t_data;

#endif
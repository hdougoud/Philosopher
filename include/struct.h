/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:28:05 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/29 19:00:15 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <pthread.h>
# include <sys/time.h>

typedef enum e_action
{
	NOTHING = 0,
	EAT = 1,
	SLEEP = 2,
	THINK = 3,
}	t_action;

typedef struct s_mutex
{
	pthread_mutex_t	mutex;
	int				var;
}	t_mutex;

typedef struct s_args
{
	int		philosophers;
	int		time_to_eat;
	int		time_to_die;
	int		time_to_sleep;
	int		must_eat;
}	t_args;

typedef struct s_global_timer
{
	pthread_mutex_t	mutex;
	int				timer;
	struct timeval	tv;
}	t_global_timer;

typedef struct s_perso_timer
{
	int				timer;
	struct timeval	tv;
}	t_perso_timer;

typedef struct s_print
{
	pthread_mutex_t	mutex;
}	t_print;

typedef struct s_global
{
	t_global_timer	*timer;
	t_args			*args;
	t_mutex			*fork;
	t_mutex			*satiated;
	t_mutex			*is_finished;
	t_print			*print;
}	t_global;

typedef struct s_data
{
	pthread_t		thread_id;
	int				philo_x;
	int				eated;
	int				owned_fork;
	int				objective_complete;
	t_action		action;
	t_perso_timer	*last_eat;
	t_perso_timer	*last_action; //used only for sleep, for the moment
	t_global_timer	*gl_timer;
	t_args			*args;
	t_mutex			*fork;
	t_mutex			*satiated;
	t_mutex			*is_finished;
	t_print			*print;
}	t_data;

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:28:05 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/06 10:46:05 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <pthread.h>
# include <sys/time.h>

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

typedef struct s_print
{
	pthread_mutex_t	mutex;
}	t_print;

typedef struct s_global
{
	struct timeval	*tv;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	t_args			*args;
	t_mutex			*satiated;
	t_mutex			*is_finished;
}	t_global;

typedef struct s_data
{
	pthread_t		thread_id;
	int				philo_x;
	int				eated;
	int				objective_complete;
	t_args			*args;
	t_mutex			*satiated;
	t_mutex			*is_finished;
	struct timeval	last_meal;
	struct timeval	nap_time;
	struct timeval	*timer;
	pthread_mutex_t	*print;
	pthread_mutex_t	*right_hand;
	pthread_mutex_t	*left_hand;
}	t_data;

#endif
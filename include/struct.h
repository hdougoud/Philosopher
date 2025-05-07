/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:28:05 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/07 19:14:48 by hdougoud         ###   ########.fr       */
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

typedef struct	s_fork
{
	pthread_mutex_t	*mutex;
	int				used;
}	t_fork;

typedef struct s_print
{
	pthread_mutex_t	mutex;
}	t_print;

typedef struct s_philo
{
	pthread_t		thread_id;
	int				philo_x;
	int				meals;
	t_fork			*right_hand;
	t_fork			*left_hand;
	struct timeval	nap_time;
}	t_philo;

typedef struct s_data
{
	int				philosophers;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				must_eat;
	t_mutex			death_check;
	t_mutex			satiated;
	struct timeval	*timer;
	pthread_mutex_t	print;
	t_philo			*philo;
}	t_data;

#endif
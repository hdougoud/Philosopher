/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:28:05 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/09 15:34:46 by hdougoud         ###   ########.fr       */
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

typedef struct s_last_meal
{
	pthread_mutex_t	mutex;
	struct timeval	tv;
}	t_last_meal;

typedef struct s_philo
{
	pthread_t		thread_id;
	int				id;
	int				meals;
	int				satiated;
	t_last_meal		last_meal;
	pthread_mutex_t	right_hand;
	pthread_mutex_t	*left_hand;
	struct timeval	nap_time;
	struct s_data *data;
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
	struct timeval	timer;
	pthread_mutex_t	print;
	t_philo			*philo;
}	t_data;

#endif
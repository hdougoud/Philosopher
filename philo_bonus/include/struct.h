/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:28:05 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/15 14:31:35 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>

# define MAX_PHILO 250

typedef struct s_last_meal
{
	pthread_t		thread;
	sem_t			*sem;
	char			sem_name[20];
	struct timeval	tv;
}	t_last_meal;
typedef struct t_end
{
	pthread_t	thread;
	sem_t		*sem;
	char		sem_name[20];
	int			status;
}	t_end;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				meals;
	t_end			end;
	t_last_meal		last_meal;
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
	sem_t			*fork;
	sem_t			*print;
	sem_t			*satiated;
	sem_t			*death_check;
	t_philo			all_philo[MAX_PHILO];
	t_philo			this_philo;
	pid_t			pid[MAX_PHILO];
	struct timeval	timer;
}	t_data;

#endif
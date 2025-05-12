/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:28:05 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/12 11:26:00 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>

typedef struct s_mutex
{
	sem_t	mutex;
	int		var;
}	t_mutex;

typedef struct s_philo
{
	pid_t			pid;
	int				meals;
	int				satiated;
	struct timeval	last_meal;
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
	sem_t			*death_check;
	sem_t			*satiated;// possibly local variable
	sem_t			*print;
	struct timeval	timer;
	t_philo			*philo;
}	t_data;

#endif
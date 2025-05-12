/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:28:05 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/12 15:06:20 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>

typedef struct s_last_meal
{
	sem_t			*sem;
	char			sem_name[20];
	struct timeval	tv;
}	t_last_meal;

typedef struct s_philo
{
	pid_t			pid;
	int				meals;
	t_last_meal		last_meal;
	struct timeval	nap_time;
	struct s_data *data;
}	t_philo;

typedef struct s_death_check
{
	sem_t	*sem;
	int		status;
}	t_death_check;
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
	t_death_check	death_check;
	struct timeval	timer;
	t_philo			*philo;
}	t_data;

#endif
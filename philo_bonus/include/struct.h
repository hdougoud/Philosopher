/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:32:02 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/06 10:16:56 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#include <semaphore.h>
#include <sys/time.h>

typedef struct s_args
{
	int		philosophers;
	int		time_to_eat;
	int		time_to_die;
	int		time_to_sleep;
	int		must_eat;
}	t_args;

typedef struct s_fork
{
	int				philo_n;
	int				meal_count;
	struct timeval	last_meal;
	struct timeval	last_nap;
}	t_fork;

typedef struct s_data
{
	t_args			*args;
	sem_t			*fork;
	sem_t			*print;
	sem_t			*satiated;
	struct timeval	timer;
}	t_data;

#endif
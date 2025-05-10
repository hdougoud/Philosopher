/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:28:05 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/10 19:15:25 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <semaphore.h>
# include <sys/time.h>

# define RED	"\x1b[31;1m"
# define GREEN	"\x1b[32;1m"
# define YELLOW	"\x1b[33;1m"
# define RESET	"\x1b[0m"

typedef struct s_mutex
{
	sem_t	mutex;
	int		var;
}	t_mutex;

typedef struct s_last_meal
{
	sem_t			mutex;
	struct timeval	tv;
}	t_last_meal;

typedef struct s_philo
{
	pthread_t		thread_id;
	int				id;
	int				meals;
	int				satiated;
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
	sem_t			fork;
	sem_t			death_check;
	sem_t			satiated;// possibly local variable
	sem_t			print;
	struct timeval	timer;
	t_philo			*philo;
}	t_data;

#endif
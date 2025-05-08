/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:22:28 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/08 14:18:15 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define DIED			"died"
# define IS_EATING		"is eating"
# define IS_THINKING	"is thinking"
# define IS_SLEEPING	"is sleeping"
# define TAKEN_FORK		"has taken a fork"

# define RED_ULTRA		"\x1b[31;1m"
# define YELLOW_ULTRA	"\x1b[33;1m"
# define RESET			"\x1b[0m"

typedef struct s_args			t_args;
typedef struct s_philo			t_philo;
typedef struct s_mutex			t_mutex;
typedef struct s_perso_timer	t_perso_timer;
typedef struct s_global_timer	t_global_timer;

int		is_ended(t_philo *philo);
int		update_local_timer(struct timeval *timer);


void	next_activity(t_philo *philo);
void	check_last_meal(t_philo *philo);
void	putstr_fd(int fd, const char *str);
void	thread_error(t_philo *philo, char *str);
void	reset_local_timer(t_perso_timer *timer);
void	print_activity(t_philo *philo, char *activity);

#endif
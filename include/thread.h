/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:22:28 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/10 19:18:27 by hdougoud         ###   ########.fr       */
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

typedef struct s_args			t_args;
typedef struct s_philo			t_philo;

int		is_ended(t_philo *philo);


void	next_activity(t_philo *philo);
void	putstr_fd(int fd, const char *str);
void	thread_error(t_philo *philo, char *str);
void	print_activity(t_philo *philo, char *activity);

#endif
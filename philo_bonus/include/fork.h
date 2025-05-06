/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:37:10 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/06 13:37:32 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORK_H
# define FORK_H

# define RED	"\x1b[31;1m"
# define GREEN	"\x1b[32;1m"
# define YELLOW	"\x1b[33;1m"
# define RESET	"\x1b[0m"

# define DIED "died"
# define IS_EATING "is eating"
# define IS_THINKING "is thinking"
# define IS_SLEEPING "is sleeping"
# define TAKEN_FORK "has taken a fork"

#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <signal.h>

typedef struct s_data t_data;
typedef struct s_fork t_fork;

void	putstr_fd(int fd, char *str);
void	start_fork(t_data *data, int philo_n);
void	next_action(t_data *data, t_fork *forks);
void	check_last_meal(t_data *data, t_fork *forks);
void	print_activity(t_data *data, t_fork *forks, char *activity);

#endif
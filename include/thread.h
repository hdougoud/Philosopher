/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:22:28 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/06 10:24:57 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

# define DIED "died"
# define IS_EATING "is eating"
# define IS_THINKING "is thinking"
# define IS_SLEEPING "is sleeping"
# define TAKEN_FORK "has taken a fork"

# define RED_ULTRA		"\x1b[31;1m"
# define YELLOW_ULTRA	"\x1b[33;1m"
# define RESET			"\x1b[0m"

typedef struct s_args			t_args;
typedef struct s_data			t_data;
typedef struct s_mutex			t_mutex;
typedef struct s_perso_timer	t_perso_timer;
typedef struct s_global_timer	t_global_timer;

int		is_ended(t_data *data);
int		update_local_timer(struct timeval *timer);

void	next_activity(t_data *data);
void	putstr_fd(int fd, char *str);
void	check_last_meal(t_data *data);
void	thread_error(t_data *data, char *str);
void	reset_local_timer(t_perso_timer *timer);
void	print_activity(t_data *data, char *activity);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:11:30 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/13 14:09:00 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORK_H
# define FORK_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

# define RED	"\x1b[31;1m"
# define GREEN	"\x1b[32;1m"
# define YELLOW	"\x1b[33;1m"
# define RESET	"\x1b[0m"

# define DIED			"died"
# define IS_EATING		"is eating"
# define IS_THINKING	"is thinking"
# define IS_SLEEPING	"is sleeping"
# define TAKEN_FORK		"has taken a fork"

typedef struct s_data	t_data;

void	putstr_fd(int fd, const char *str);
void	clean_exit(t_data *data, const int id);
void	next_action(t_data *data, const int id);
void	check_the_end(t_data *data, const int id);
void	print_fork_error(t_data *data, const int id, char *str);
void	print_activity(t_data *data, const int id, const char *activity);

#endif
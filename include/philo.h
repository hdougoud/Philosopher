/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:27:52 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/11 01:36:44 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define DIED			"died"
# define IS_EATING		"is eating"
# define IS_THINKING	"is thinking"
# define IS_SLEEPING	"is sleeping"
# define TAKEN_FORK		"has taken a fork"

# define RED	"\x1b[31;1m"
# define GREEN	"\x1b[32;1m"
# define YELLOW	"\x1b[33;1m"
# define RESET	"\x1b[0m"

typedef struct s_args	t_args;
typedef struct s_data	t_data;

int		ft_atoi(const char *str);
int		monitoring(t_data *data);
int		init_philosophers(t_data *data);
int		print_error(pthread_mutex_t *print, const char *str);

void	*exec_thread(void *thread);
void	putstr_fd(int fd, const char *str);
void	*ft_calloc(size_t count, size_t size);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:27:52 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/20 18:11:04 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# ifndef PTHREAD_THREADS_MAX
#  define PTHREAD_THREADS_MAX 1024
# endif

# define COLOR_RED			"\x1b[31m"
# define COLOR_RED_ULTRA	"\x1b[31;1m"
# define COLOR_YELLOW		"\x1b[33m"
# define COLOR_YELLOW_ULTRA	"\x1b[33m;1m"
# define COLOR_RESET		"\x1b[0m"

typedef struct s_global_timer t_global_timer;

int		ft_atoi(const char *str);
int		set_timer(struct timeval *tv, int *timer);

char	*ft_strjoin(char const *s1, char const *s2);

void	print_error(const char *str);
void	*execute_philo(void *pthread);
void	*ft_calloc(size_t count, size_t size);
void	print_error_code(const char *function, int err_code);

size_t	ft_strlen(const char *str);

t_global_timer	*init_timer_struct(int *timer, struct timeval *tv);

#endif
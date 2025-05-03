/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:27:52 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/02 18:31:02 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <errno.h>

# ifndef PTHREAD_THREADS_MAX
#  define PTHREAD_THREADS_MAX 1024
# endif

# define RED			"\x1b[31m"
# define RED_ULTRA		"\x1b[31;1m"
# define GREEN_ULTRA	"\x1b[32;1m"
# define YELLOW			"\x1b[33m"
# define YELLOW_ULTRA	"\x1b[33;1m"
# define RESET			"\x1b[0m"

typedef struct s_args	t_args;
typedef struct s_data	t_data;
typedef struct s_global	t_global;

int				ft_atoi(const char *str);
int				join_all_thread(t_data **data, int n_threads);
int				init_philosophers(t_data ***data, t_args *args, t_global **gl,
					int n_thread);

char			*ft_strjoin(char const *s1, char const *s2);

void			*exec_thread(void *thread);
void			putstr_fd(int fd, char *str);
void			print_error(const char *str);
void			*ft_calloc(size_t count, size_t size);
void			free_all(t_data **data, t_global *global);
void			print_error_code(const char *function, int err_code);

size_t			ft_strlen(const char *str);

struct timeval	*init_global_timer(void);

#endif
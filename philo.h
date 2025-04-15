/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:27:52 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/15 17:25:44 by hdougoud         ###   ########.fr       */
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

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	unsigned int	fork;
}	t_fork;

typedef struct s_philo
{
	pthread_t	thread;
	int			x_philo;
}	t_philo;
typedef struct s_data
{
	int		n_philosophers;
	int		time_to_eat;
	int		time_to_die;
	int		time_to_sleep;
	int		must_eat;
	t_philo	**philo;
}	t_data;

int		ft_atoi(const char *str);

char	*ft_strjoin(char const *s1, char const *s2);

void	print_error(char *str);
void	init_struct(t_data *data);
void	init_philosophers(t_data *data, int n_thread);
void	*execute_philo(void *pthread);
void	*ft_calloc(size_t count, size_t size);


size_t	ft_strlen(const char *str);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:27:52 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/09 15:14:18 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define RED	"\x1b[31;1m"
# define GREEN	"\x1b[32;1m"
# define YELLOW	"\x1b[33;1m"
# define RESET	"\x1b[0m"

typedef struct s_args	t_args;
typedef struct s_data	t_data;
typedef struct s_global	t_global;

int		ft_atoi(const char *str);
int		monitoring(t_data *data);
int		print_error(const char *str);
int		init_philosophers(t_data *data);

void	*exec_thread(void *thread);
void	putstr_fd(int fd, const char *str);
void	*ft_calloc(size_t count, size_t size);

size_t	ft_strlen(const char *str);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:02:31 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/05 13:47:24 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define RED	"\x1b[31;1m"
# define GREEN	"\x1b[32;1m"
# define YELLOW	"\x1b[33;1m"
# define RESET	"\x1b[0m"

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

typedef struct s_args t_args;
typedef struct s_data t_data;

int	check_errors(int *error);
int	ft_atoi(const char *str);
int	init_data(t_data *data, t_args *args);

void	close_all(t_data *data);
void	putstr_fd(int fd, char *str);
void	start_monitoring(t_data *data);
void	*ft_calloc(size_t count, size_t size);

size_t	ft_strlen(const char *str);

#endif
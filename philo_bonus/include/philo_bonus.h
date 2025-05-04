/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:02:31 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/04 15:39:41 by hdougoud         ###   ########.fr       */
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
#include <stdlib.h>

int	ft_atoi(const char *str);

void	putstr_fd(int fd, char *str);

size_t	ft_strlen(const char *str);

#endif
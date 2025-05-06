/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:37:10 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/05 20:43:09 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORK_H
# define FORK_H

# define RED	"\x1b[31;1m"
# define GREEN	"\x1b[32;1m"
# define YELLOW	"\x1b[33;1m"
# define RESET	"\x1b[0m"

#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <signal.h>

typedef struct s_data t_data;

void	putstr_fd(int fd, char *str);
void	start_fork(t_data *data, int philo_n);

#endif
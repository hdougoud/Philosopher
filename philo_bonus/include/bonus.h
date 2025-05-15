/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:08:57 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/15 17:08:57 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <semaphore.h>
# include <sys/time.h>

# define RED	"\x1b[31;1m"
# define GREEN	"\x1b[32;1m"
# define YELLOW	"\x1b[33;1m"
# define RESET	"\x1b[0m"

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

int		ft_atoi(const char *str);
int		print_error(sem_t *print, const char *str);
int		init_philosophers(t_data *data);

void	free_all(t_data *data);
void	putstr_fd(int fd, const char *str);
void	*ft_calloc(size_t count, size_t size);
void	start_routine(t_data *data, int id);
void	print_activity(t_data *data, const int id, const char *activity);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:27:52 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/13 15:52:54 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>

# define COLOR_RED			"\x1b[31m"
# define COLOR_RED_ULTRA	"\x1b[31;1m"
# define COLOR_YELLOW		"\x1b[33m"
# define COLOR_YELLOW_ULTRA	"\x1b[33m;1m"
# define COLOR_RESET		"\x1b[0m"

typedef struct s_philo
{
	int	philosophers;
	int	time_to_eat;
	int	time_to_die;
	int	time_to_sleep;
	int	must_eat;
	int	fork;
}	t_philo;

int		ft_atoi(const char *str);

char	*ft_strjoin(char const *s1, char const *s2);

void	print_error(char *str);

size_t	ft_strlen(const char *str);


#endif
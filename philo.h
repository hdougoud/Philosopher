/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:27:52 by hayden            #+#    #+#             */
/*   Updated: 2025/02/17 16:58:24 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>

typedef struct s_philo
{
	int	philosophers;
	int	time_to_eat;
	int	time_to_die;
	int	time_to_sleep;
	int	must_eat;
	int	fork;
}	t_philo;

int	ft_atoi(const char *str);

#endif
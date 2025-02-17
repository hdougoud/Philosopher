/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:27:52 by hayden            #+#    #+#             */
/*   Updated: 2025/02/17 15:30:17 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

# include <stdlib.h>
# include <stdio.h>

typedef struct s_philo
{
	int	philosophers;
	int	time_to_eat;
	int	time_to_die;
	int	time_to_sleep;
	int	must_eat;
}	t_philo;

int	ft_atoi(const char *str);

#endif
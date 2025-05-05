/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:32:02 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/05 13:56:03 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#include <semaphore.h>

typedef struct s_args
{
	int		philosophers;
	int		time_to_eat;
	int		time_to_die;
	int		time_to_sleep;
	int		must_eat;
}	t_args;

typedef struct s_data
{
	t_args	*args;
	sem_t	*fork;
	sem_t	*print;
	sem_t	*finished;
	sem_t	*timer;
}	t_data;

#endif
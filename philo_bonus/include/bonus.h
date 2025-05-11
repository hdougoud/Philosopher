/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:08:57 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/11 20:49:02 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

int		ft_atoi(const char *str);

void	putstr_fd(int fd, const char *str);
void	*ft_calloc(size_t count, size_t size);

#endif

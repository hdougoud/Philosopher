/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:15:02 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/11 01:38:02 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

size_t	ft_strlen(const char *str);

static int	is_total_too_high(long total)
{
	if (total > 2147483647)
		return (putstr_fd(2, RED"Number is too high\n"RESET), -1);
	return ((int)total);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	total;

	i = 0;
	total = 0;
	if (ft_strlen(str) > 12)
		return (putstr_fd(2, RED"Number is too high\n"RESET), -1);
	while ((str[i] >= '\t' && str[i] <= '\r') || (str[i] == ' '))
	{
		if ((str[i] != '+' && str[i] != '-') && (str[i] < '0' && str[i] > '9'))
			return (putstr_fd(2, RED"Only number allowed\n"RESET), -1);
		i++;
	}
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		return (putstr_fd(2, RED"Only positiv number allowed\n"RESET), -1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		total = total * 10 + (str[i] - 48);
		i++;
	}
	if (str[i])
		return (putstr_fd(2, RED"Only number allowed\n"RESET), -1);
	return (is_total_too_high(total));
}

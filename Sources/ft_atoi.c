/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:15:02 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/24 10:34:58 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || (str[i] == ' '))
	{
		if ((str[i] != '+' && str[i] != '-') && (str[i] < '0' && str[i] > '9'))
			return (putstr_fd(2, RED"Only number allowed\n"RESET),-1);
		i++;
	}
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		return (putstr_fd(2, RED"Only positiv number allowed\n"RESET),-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		total = total * 10 + (str[i] - 48);
		i++;
	}
	if (str[i])
		return (putstr_fd(2, RED"Only number allowed\n"RESET),-1); //check leak with no valid number
	return (total);
}

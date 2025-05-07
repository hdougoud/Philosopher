/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:43:54 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/02 14:47:48 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_error_code(const char *function, int err_code)
{
	putstr_fd(2, RED);
	putstr_fd(2, function);
	if (err_code == EAGAIN)
		putstr_fd(2, "Resource temporarily unavailable");
	else if (err_code == EPERM)
		putstr_fd(2, "Operation not permitted");
	else if (err_code == EINVAL)
		putstr_fd(2, "Invalid argument");
	else if (err_code == ESRCH)
		putstr_fd(2, "No such process");
	else if (err_code == EDEADLK)
		putstr_fd(2, "Resource deadlock avoided");
	else
		putstr_fd(2, "Unknown error");
	putstr_fd(2, YELLOW"\nExit Program\n"RESET);
}

void	print_error(const char *str)
{
	putstr_fd(2, RED);
	putstr_fd(2, str);
	putstr_fd(2,YELLOW"\nExit Program\n"RESET);
}

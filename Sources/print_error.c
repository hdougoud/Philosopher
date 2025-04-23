/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:43:54 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/23 13:14:17 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	unknow_error(const char *function)
{
	char *error;

	error = ft_strjoin(function, "unknow error");
	if (!error)
		print_error("Malloc : Allocation memory failed");
	print_error(error);
}

void	print_error_code(const char *function, int err_code)
{
	char *error;

	error = NULL;
	if (err_code == EAGAIN)
		error = ft_strjoin(function, "Resource temporarily unavailable");
	else if (err_code == EPERM)
		error = ft_strjoin(function, "Operation not permitted");
	else if (err_code == EINVAL)
		error = ft_strjoin(function, "Invalid argument");
	else if (err_code == ESRCH)
		error = ft_strjoin(function, "No such process");
	else if (err_code == EDEADLK)
		error = ft_strjoin(function, "Resource deadlock avoided");
	else
	{
		unknow_error(function);
		return ;
	}
	if (error == NULL)
		print_error("Malloc : Allocation memory failed");
	print_error(error);
}

void	print_error(const char *str)
{
	char *color;
	char *error;

	usleep(1000);
	color = ft_strjoin(COLOR_RED, str);
	if (!color)
	{
		write(2, COLOR_RED"Print_error : Allocation memory failed\n", 44);
		write(2, COLOR_YELLOW"Exit program\n"COLOR_RESET, 18);
		exit(EXIT_FAILURE);
	}
	error = ft_strjoin(color, COLOR_YELLOW"\nExit Program\n"COLOR_RESET);
	if (!error)
	{
		free(color);
		write(2, COLOR_RED"Print_error : Allocation memory failed\n", 44);
		write(2, COLOR_YELLOW"Exit program\n"COLOR_RESET, 18);
		exit(EXIT_FAILURE);
	}
	write(2, error, ft_strlen(error));
	free(color);
	free(error);
	exit(EXIT_FAILURE); //exit is unautorised
}


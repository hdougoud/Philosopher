/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:43:54 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/20 18:12:14 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_error_code(const char *function, int err_code)
{
	char *error;

	error = NULL;
	printf("%d\n", err_code);
	if (err_code == 35)
		error = ft_strjoin(function, "Resource temporarily unavailable");
	else
	{
		print_error(function);
		return ;
	}
	if (error == NULL)
		print_error("Print_error : Allocation memory failed");
	else 
		print_error(error);
}

void	print_error(const char *str)
{
	char *color;
	char *error;

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


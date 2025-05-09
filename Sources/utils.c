/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:01:46 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/09 19:29:13 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	print_error(pthread_mutex_t *print, const char *str)
{
	pthread_mutex_lock(print);
	putstr_fd(2, RED"Error\n");
	putstr_fd(2, str);
	putstr_fd(2, YELLOW"\nExit Program\n"RESET);
	pthread_mutex_unlock(print);
	return (1);
}

static void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *) s;
	while (n > i)
	{
		ptr[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == 0)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	putstr_fd(int fd, const char *str)
{
	size_t	len;

	len = ft_strlen(str);
	write(fd, str, len);
}

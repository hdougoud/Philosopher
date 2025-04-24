/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:01:46 by hdougoud          #+#    #+#             */
/*   Updated: 2025/04/24 15:23:56 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/**
 * @brief Concatenates two strings into a newly allocated string.
 * @param s1 the first string.
 * @param s2 the second string.
 * @return A newly allocated string containing the concatenation of `s1` and
 *         `s2`, or NULL if the allocation fails or if `s1` or `s2` is NULL.
 * @warning This function does not free S1 or S2 when in use.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (str == 0)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

void	putstr_fd(int fd, char *str)
{
	size_t	len;

	len = ft_strlen(str);
	write(fd, str, len);
}

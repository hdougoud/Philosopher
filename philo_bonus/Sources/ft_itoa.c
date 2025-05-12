/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:38:06 by hdougoud          #+#    #+#             */
/*   Updated: 2025/05/12 13:16:34 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static char	*ft_convert(int n, int len, char *str)
{
	str[len] = '\0';
	len--;
	while (len >= 0)
	{
		str[len] = (n % 10) + '0';
		len --;
		n /= 10;
	}
	return (str);
}

char	*ft_itoa(int n, char *str)
{
	int		len;
	int		div;

	div = 1;
	len = 1;
	while (n / div > 9)
	{
		len++;
		div *= 10;
	}
	return (ft_convert(n, len, str));
}

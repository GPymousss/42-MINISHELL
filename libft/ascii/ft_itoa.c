/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <gletilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 04:58:24 by gletilly          #+#    #+#             */
/*   Updated: 2025/01/12 23:03:52 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_strlen_itoa(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	ft_number_itoa(char *s, int n)
{
	if (n < 0)
	{
		*s++ = '-';
		n = -n;
	}
	if (n >= 10)
	{
		ft_number_itoa(s, n / 10);
		while (*s)
			s++;
	}
	*s = (n % 10) + '0';
	*(s + 1) = '\0';
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	if (n == 0)
		return (ft_strdup("0"));
	len = ft_strlen_itoa(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	ft_number_itoa(str, n);
	return (str);
}

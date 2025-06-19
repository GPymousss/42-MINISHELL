/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <gletilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:48:02 by lomont            #+#    #+#             */
/*   Updated: 2025/05/27 00:17:32 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

long	ft_atol(const char *str)
{
	long	nb;
	int		sign;
	size_t	i;

	i = 0;
	nb = 0;
	sign = 1;
	while (ft_isspace(str[i]) == 1)
		i++;
	if ((str[i] == '+' && str[i + 1] != '-'))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] != '\0' && ft_isdigit(str[i]))
	{
		nb *= 10;
		nb += str[i] - '0';
		i++;
	}
	nb = nb * sign;
	return (nb);
}

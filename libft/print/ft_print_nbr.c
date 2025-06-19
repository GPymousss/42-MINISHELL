/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <gletilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 01:00:48 by lomont            #+#    #+#             */
/*   Updated: 2025/05/27 00:15:35 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_print_nbr(int n)
{
	int	counter;

	counter = 0;
	if (n == -2147483648)
	{
		return (ft_print_str("-2147483648"));
	}
	if (n < 0)
	{
		counter += ft_print_char('-');
		n = -n;
	}
	if (n >= 10)
	{
		counter += ft_print_nbr(n / 10);
		counter += ft_print_char((n % 10) + '0');
	}
	else
	{
		counter += ft_print_char(n + '0');
	}
	return (counter);
}

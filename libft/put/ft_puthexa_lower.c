/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa_lower.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <gletilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:52:32 by lomont            #+#    #+#             */
/*   Updated: 2025/05/27 00:15:05 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_puthexa_lower(unsigned int n)
{
	char	*base16;
	int		counter;

	counter = 0;
	base16 = "0123456789abcdef";
	if (n >= 16)
		counter += ft_puthexa_lower(n / 16);
	counter += ft_print_char(base16[n % 16]);
	return (counter);
}

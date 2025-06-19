/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexaptr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <gletilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:56:50 by lomont            #+#    #+#             */
/*   Updated: 2025/05/27 00:15:38 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_print_hexaptr(void *n)
{
	int				counter;
	unsigned long	address;

	address = (unsigned long) n;
	counter = 0;
	if (address == 0)
	{
		write (1, "(nil)", 5);
		return (counter += 5);
	}
	counter += ft_print_str("0x");
	counter += ft_puthexa_ptr(address);
	return (counter);
}

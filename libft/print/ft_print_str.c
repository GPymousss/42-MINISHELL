/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <gletilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 01:01:48 by lomont            #+#    #+#             */
/*   Updated: 2025/05/27 00:15:33 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_print_str(char *s)
{
	int	counter;

	counter = 0;
	if (!s)
	{
		write (1, "(null)", 6);
		return (counter += 6);
	}
	while (*s)
	{
		write(1, &*s, 1);
		s++;
		counter++;
	}
	return (counter);
}

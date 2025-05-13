/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <gletilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 23:34:34 by gletilly          #+#    #+#             */
/*   Updated: 2025/01/12 23:02:05 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	index;
	size_t			len;

	if (s && f)
	{
		len = ft_strlen(s);
		index = 0;
		while (index < len)
		{
			f(index, &s[index]);
			index++;
		}
		s[index] = '\0';
	}
}

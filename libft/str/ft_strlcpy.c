/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <gletilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 00:04:54 by miniklar          #+#    #+#             */
/*   Updated: 2025/05/27 00:14:29 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	srclen;

	srclen = ft_strlen(src);
	if (srclen + 1 < size)
		ft_memcpy(dest, src, srclen + 1);
	else if (size != 0)
	{
		ft_memcpy(dest, src, size - 1);
		dest[size - 1] = 0;
	}
	return (srclen);
}

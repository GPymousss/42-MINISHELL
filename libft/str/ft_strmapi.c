/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <gletilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 23:09:30 by gletilly          #+#    #+#             */
/*   Updated: 2025/01/12 23:02:15 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	index;
	char			*copy;
	size_t			len;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	copy = (char *)malloc(len + 1);
	if (!copy)
		return (NULL);
	index = 0;
	while (index < len)
	{
		copy[index] = f(index, s[index]);
		index++;
	}
	copy[index] = '\0';
	return (copy);
}

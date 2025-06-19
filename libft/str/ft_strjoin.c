/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <gletilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:37:41 by miniklar          #+#    #+#             */
/*   Updated: 2025/05/27 00:14:35 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*new_s;
	size_t	lens1;
	size_t	lens2;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	new_s = malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (!new_s)
		return (NULL);
	ft_memcpy(new_s, s1, lens1);
	ft_memcpy(new_s + lens1, s2, lens2);
	new_s[lens1 + lens2] = '\0';
	return (new_s);
}

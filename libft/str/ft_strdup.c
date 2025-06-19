/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <gletilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:29:13 by lomont            #+#    #+#             */
/*   Updated: 2025/05/27 00:14:41 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s)
{
	char	*tmp;
	size_t	srclen;

	srclen = ft_strlen(s) + 1;
	tmp = malloc(srclen * sizeof(char));
	if (!tmp)
		return (NULL);
	ft_memmove(tmp, s, srclen);
	return (tmp);
}

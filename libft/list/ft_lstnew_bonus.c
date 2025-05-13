/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <gletilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 02:11:43 by gletilly          #+#    #+#             */
/*   Updated: 2025/01/12 23:03:23 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*copy;

	copy = (t_list *)malloc(sizeof(t_list));
	if (!copy)
		return (NULL);
	copy->content = content;
	copy->next = NULL;
	return (copy);
}

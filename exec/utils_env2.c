/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <gletilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:00:00 by gletilly          #+#    #+#             */
/*   Updated: 2025/06/19 12:00:00 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*alloc_envp_string(char **envp, int i, int k)
{
	char	*str;

	str = malloc(sizeof(char) * (k + 1));
	if (!str)
		return (NULL);
	ft_memmove(str, envp[i], k);
	str[k] = '\0';
	return (str);
}

char	**ft_malloc_envp(char **envp)
{
	char	**alloc_envp;
	int		i;
	int		k;

	i = 0;
	while (envp[i])
		i++;
	alloc_envp = malloc(sizeof(char *) * (i + 1));
	if (!alloc_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		k = 0;
		while (envp[i][k] != '\0')
			k++;
		alloc_envp[i] = alloc_envp_string(envp, i, k);
		if (!alloc_envp[i])
			return (free_array_partial(alloc_envp, i));
		i++;
	}
	alloc_envp[i] = NULL;
	return (alloc_envp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:29:35 by lomont            #+#    #+#             */
/*   Updated: 2025/07/04 23:01:08 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*get_env_value_from_envp(char *name, char **envp)
{
	int		i;
	size_t	len;

	if (!name || !envp)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (ft_strdup(envp[i] + len + 1));
		i++;
	}
	return (NULL);
}

char	*get_env_value_from_list(char *name, t_envp *env)
{
	t_envp	*cur;

	if (!name || !env)
		return (NULL);
	cur = env;
	while (cur)
	{
		if (ft_strcmp(cur->key, name) == 0)
			return (ft_strdup(cur->value));
		cur = cur->next;
	}
	return (NULL);
}

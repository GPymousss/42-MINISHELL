/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:00:00 by llangana          #+#    #+#             */
/*   Updated: 2025/06/19 12:00:00 by llangana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"

char	*get_specific_env(char **envp, char *env)
{
	size_t	i;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], env, ft_strlen(env)) == 0)
			return (ft_substr(envp[i], ft_strlen(env),
					ft_strlen(envp[i]) - ft_strlen(env)));
		i++;
	}
	return (NULL);
}

char	*get_prev_pwd(char **envp)
{
	size_t	i;
	char	*current_pwd;

	current_pwd = get_specific_env(envp, "PWD");
	if (ft_strncmp(current_pwd, "/home\0", ft_strlen(current_pwd)) == 0)
		return (ft_strdup("/"));
	i = ft_strlen(current_pwd);
	while (current_pwd[i] != '/')
		i--;
	return (ft_substr(current_pwd, 0, i));
}

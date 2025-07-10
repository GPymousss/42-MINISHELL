/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 05:21:55 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/10 05:21:55 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_valid_unset_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	find_env_variable_index(char **envp, char *var_name)
{
	int	i;
	int	len;

	if (!envp || !var_name)
		return (-1);
	len = ft_strlen(var_name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, len) == 0 && envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	remove_env_variable(char **envp, int index)
{
	int	i;

	if (index < 0 || !envp || !envp[index])
		return ;
	free(envp[index]);
	i = index;
	while (envp[i + 1])
	{
		envp[i] = envp[i + 1];
		i++;
	}
	envp[i] = NULL;
}

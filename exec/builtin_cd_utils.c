/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 05:30:00 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/05 05:30:00 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	find_env_var_index(char **envp, char *var_name)
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

static void	update_env_variable(char **envp, char *var_name, char *value)
{
	int		index;
	char	*temp;

	index = find_env_var_index(envp, var_name);
	if (index >= 0)
	{
		free(envp[index]);
		temp = ft_strjoin(var_name, "=");
		envp[index] = ft_strjoin_free(temp, ft_strdup(value));
	}
}

void	update_pwd_variables(t_shell *shell, char *old_pwd)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return ;
	if (old_pwd)
		update_env_variable(shell->envp, "OLDPWD", old_pwd);
	update_env_variable(shell->envp, "PWD", new_pwd);
	free(new_pwd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 22:47:40 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/05 22:47:40 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	*get_env_var_value(t_shell *shell, char *key)
{
	t_envp	*node;

	node = find_env_node(shell->env, key);
	if (node)
		return (node->value);
	return (NULL);
}

static char	*resolve_cd_path(t_shell *shell, char *path)
{
	char	*home_value;
	char	*oldpwd_value;

	if (!path || ft_strcmp(path, "~") == 0)
	{
		home_value = get_env_var_value(shell, "HOME");
		if (!home_value)
		{
			ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
			return (NULL);
		}
		return (ft_strdup(home_value));
	}
	if (ft_strcmp(path, "-") == 0)
	{
		oldpwd_value = get_env_var_value(shell, "OLDPWD");
		if (!oldpwd_value)
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
			return (NULL);
		}
		ft_putendl_fd(oldpwd_value, STDOUT_FILENO);
		return (ft_strdup(oldpwd_value));
	}
	return (ft_strdup(path));
}

static void	update_pwd_vars(t_shell *shell, char *old_pwd)
{
	char		*new_pwd;
	t_envp		*pwd_node;
	t_envp		*oldpwd_node;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return ;
	oldpwd_node = find_env_node(shell->env, "OLDPWD");
	if (oldpwd_node && old_pwd)
		update_env_node(oldpwd_node, old_pwd);
	else if (old_pwd)
		add_env_node(shell, "OLDPWD", old_pwd);
	pwd_node = find_env_node(shell->env, "PWD");
	if (pwd_node)
		update_env_node(pwd_node, new_pwd);
	else
		add_env_node(shell, "PWD", new_pwd);
	rebuild_envp_array(shell);
	free(new_pwd);
}

static int	handle_cd_error(char *target_path, char *old_pwd)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(target_path, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	free(target_path);
	if (old_pwd)
		free(old_pwd);
	return (1);
}

int	builtin_cd(t_shell *shell, t_cmd *cmd)
{
	char	*target_path;
	char	*old_pwd;

	if (!shell || !cmd || !cmd->args)
		return (1);
	if (cmd->args[1] && cmd->args[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (1);
	}
	old_pwd = getcwd(NULL, 0);
	target_path = resolve_cd_path(shell, cmd->args[1]);
	if (!target_path)
	{
		if (old_pwd)
			free(old_pwd);
		return (1);
	}
	if (chdir(target_path) == -1)
		return (handle_cd_error(target_path, old_pwd));
	update_pwd_vars(shell, old_pwd);
	free(target_path);
	if (old_pwd)
		free(old_pwd);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 05:30:00 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/05 05:30:00 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_valid_export_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	export_with_value(t_shell *shell, char *key, char *value)
{
	t_envp	*existing_node;

	existing_node = find_env_node(shell->env, key);
	if (existing_node)
		update_env_node(existing_node, value);
	else
		add_env_node(shell, key, value);
	rebuild_envp_array(shell);
	return (0);
}

static int	process_export_argument(t_shell *shell, char *arg)
{
	char	*equal_pos;
	char	*key;
	char	*value;
	int		result;

	if (!is_valid_export_identifier(arg))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return (1);
	}
	equal_pos = ft_strchr(arg, '=');
	if (!equal_pos)
		return (0);
	key = ft_substr(arg, 0, equal_pos - arg);
	value = equal_pos + 1;
	result = export_with_value(shell, key, value);
	free(key);
	return (result);
}

int	builtin_export(t_shell *shell, t_cmd *cmd)
{
	int	i;
	int	exit_status;

	if (!shell || !cmd || !cmd->args)
		return (1);
	if (!cmd->args[1])
		return (builtin_env(shell, cmd));
	exit_status = 0;
	i = 1;
	while (cmd->args[i])
	{
		if (process_export_argument(shell, cmd->args[i]) != 0)
			exit_status = 1;
		i++;
	}
	return (exit_status);
}

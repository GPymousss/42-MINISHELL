/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 22:18:44 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/09 07:06:58 by llangana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_shell *shell, t_cmd *cmd)
{
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (builtin_pwd(shell, cmd));
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (builtin_cd(shell, cmd));
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (builtin_echo(shell, cmd));
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (builtin_env(shell, cmd));
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (builtin_export(shell, cmd));
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (builtin_unset(shell, cmd));
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (builtin_exit(shell, cmd));
	return (1);
}

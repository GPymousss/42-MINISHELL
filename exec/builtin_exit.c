/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 05:21:11 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/10 05:21:11 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_numeric(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	cleanup_and_exit(t_shell *shell, int exit_code)
{
	if (shell->stdin_backup != -1)
		close(shell->stdin_backup);
	if (shell->stdout_backup != -1)
		close(shell->stdout_backup);
	free_shell(shell);
	exit(exit_code);
}

int	builtin_exit(t_shell *shell, t_cmd *cmd)
{
	int	exit_code;

	if (!cmd->args[1])
		cleanup_and_exit(shell, shell->exit_status);
	if (!is_numeric(cmd->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		cleanup_and_exit(shell, 2);
	}
	if (cmd->args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	exit_code = ft_atoi(cmd->args[1]);
	cleanup_and_exit(shell, exit_code);
	return (0);
}

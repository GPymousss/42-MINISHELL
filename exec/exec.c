/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 04:37:06 by gletilly          #+#    #+#             */
/*   Updated: 2025/09/05 16:31:21 by llangana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "../builtins/builtins.h"

static int	has_pipes(t_cmd *cmds)
{
	return (cmds && cmds->next != NULL);
}

int	backup_std_fds(t_shell *shell)
{
	if (shell->stdin_backup >= 0)
		close(shell->stdin_backup);
	if (shell->stdout_backup >= 0)
		close(shell->stdout_backup);
	shell->stdin_backup = dup(STDIN_FILENO);
	shell->stdout_backup = dup(STDOUT_FILENO);
	if (shell->stdin_backup == -1 || shell->stdout_backup == -1)
	{
		if (shell->stdin_backup != -1)
			close(shell->stdin_backup);
		if (shell->stdout_backup != -1)
			close(shell->stdout_backup);
		return (-1);
	}
	return (0);
}

void	restore_std_fds(t_shell *shell)
{
	dup2(shell->stdin_backup, STDIN_FILENO);
	dup2(shell->stdout_backup, STDOUT_FILENO);
	close(shell->stdin_backup);
	close(shell->stdout_backup);
	shell->stdin_backup = -1;
	shell->stdout_backup = -1;
}

int	exec(t_shell *shell)
{
	int	exit_status;

	if (!shell || !shell->cmds)
		return (1);
	if (has_pipes(shell->cmds))
		exit_status = execute_pipeline(shell, shell->cmds);
	else
		exit_status = execute_single_cmd(shell, shell->cmds);
	shell->exit_status = exit_status;
	return (exit_status);
}

int	execute_single_cmd(t_shell *shell, t_cmd *cmd)
{
	int	exit_status;

	if (!cmd)
		return (1);
	if (!cmd->args || !cmd->args[0])
	{
		if (!cmd->redir)
			return (1);
		return (handle_redirs_only(shell, cmd));
	}
	if (backup_std_fds(shell) == -1)
		return (1);
	if (apply_redirections(shell, cmd) == -1)
	{
		restore_std_fds(shell);
		return (1);
	}
	if (is_builtin(cmd->args[0]))
		exit_status = execute_builtin(shell, cmd);
	else
		exit_status = execute_external_cmd(shell, cmd);
	restore_std_fds(shell);
	return (exit_status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 04:37:06 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/05 04:37:06 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"

static int	has_pipes(t_cmd *cmds)
{
	return (cmds && cmds->next != NULL);
}

static int	backup_std_fds(int *stdin_backup, int *stdout_backup)
{
	*stdin_backup = dup(STDIN_FILENO);
	*stdout_backup = dup(STDOUT_FILENO);
	if (*stdin_backup == -1 || *stdout_backup == -1)
		return (-1);
	return (0);
}

static void	restore_std_fds(int stdin_backup, int stdout_backup)
{
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
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
	int	stdin_backup;
	int	stdout_backup;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (backup_std_fds(&stdin_backup, &stdout_backup) == -1)
		return (1);
	if (apply_redirections(cmd) == -1)
	{
		restore_std_fds(stdin_backup, stdout_backup);
		return (1);
	}
	if (is_builtin(cmd->args[0]))
		exit_status = execute_builtin(shell, cmd);
	else
		exit_status = execute_external_cmd(shell, cmd);
	restore_std_fds(stdin_backup, stdout_backup);
	return (exit_status);
}

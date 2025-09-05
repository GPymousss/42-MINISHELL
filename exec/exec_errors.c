/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 04:38:27 by gletilly          #+#    #+#             */
/*   Updated: 2025/09/05 16:28:08 by llangana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	close_backup_in_child(t_shell *shell)
{
	if (shell->stdin_backup != -1)
		close(shell->stdin_backup);
	if (shell->stdout_backup != -1)
		close(shell->stdout_backup);
}

void	handle_exec_error(char *cmd, int error_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	if (error_code == CMD_NOT_FOUND)
		ft_putendl_fd(": command not found", STDERR_FILENO);
	else if (error_code == PERMISSION_DENIED)
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	else
		ft_putendl_fd(": unknown error", STDERR_FILENO);
}

int	check_pipeline_syntax(t_cmd *cmds)
{
	t_cmd	*current;

	current = cmds;
	while (current)
	{
		if (!current->args || !current->args[0])
		{
			ft_putendl_fd(
				"minishell: syntax error near unexpected token `|'",
				STDERR_FILENO);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

int	handle_redirs_only(t_shell *shell, t_cmd *cmd)
{
	if (backup_std_fds(shell) == -1)
		return (1);
	if (apply_redirections(shell, cmd) == -1)
	{
		restore_std_fds(shell);
		return (1);
	}
	restore_std_fds(shell);
	return (shell->exit_status);
}

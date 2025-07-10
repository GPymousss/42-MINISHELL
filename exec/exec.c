/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 05:22:31 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/10 05:22:31 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"

static int	has_pipes(t_cmd *cmds)
{
	return (cmds && cmds->next != NULL);
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
	int	saved_stdin;
	int	saved_stdout;
	int	result;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (setup_redirections(cmd->redir) != 0)
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		return (1);
	}
	if (is_builtin(cmd->args[0]))
		result = execute_builtin(shell, cmd);
	else
		result = execute_external_cmd(shell, cmd);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (result);
}

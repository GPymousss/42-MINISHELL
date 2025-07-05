/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 04:37:26 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/05 04:37:26 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	handle_child_process(t_shell *shell, t_cmd *cmd, char *cmd_path)
{
	if (execve(cmd_path, cmd->args, shell->envp) == -1)
	{
		handle_exec_error(cmd->args[0], PERMISSION_DENIED);
		free(cmd_path);
		exit(PERMISSION_DENIED);
	}
	return (0);
}

int	execute_external_cmd(t_shell *shell, t_cmd *cmd)
{
	char	*cmd_path;
	pid_t	pid;
	int		status;

	cmd_path = find_command_path(cmd->args[0], shell->envp);
	if (!cmd_path)
	{
		handle_exec_error(cmd->args[0], CMD_NOT_FOUND);
		return (CMD_NOT_FOUND);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(cmd_path);
		return (1);
	}
	if (pid == 0)
		handle_child_process(shell, cmd, cmd_path);
	free(cmd_path);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

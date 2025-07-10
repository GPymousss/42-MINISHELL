/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 05:23:05 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/10 05:23:05 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtins.h"

static void	close_all_pipes(int **pipes, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

static void	setup_child_pipes(int **pipes, int cmd_index, int cmd_count)
{
	if (cmd_index > 0)
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
	if (cmd_index < cmd_count - 1)
		dup2(pipes[cmd_index][1], STDOUT_FILENO);
	close_all_pipes(pipes, cmd_count);
}

void	execute_pipe_child(t_shell *shell, t_cmd *cmd, t_pipe_data *data)
{
	setup_child_pipes(data->pipes, data->cmd_index, data->cmd_count);
	if (apply_redirections(cmd) == -1)
		exit(1);
	if (is_builtin(cmd->args[0]))
	{
		shell->exit_status = execute_builtin(shell, cmd);
		exit(shell->exit_status);
	}
	else
	{
		shell->exit_status = execute_external_cmd(shell, cmd);
		exit(shell->exit_status);
	}
}

int	wait_for_pipeline(pid_t *pids, int **pipes, int cmd_count)
{
	int	*statuses;
	int	i;
	int	final_status;

	close_all_pipes(pipes, cmd_count);
	statuses = malloc(sizeof(int) * cmd_count);
	if (!statuses)
		return (1);
	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &statuses[i], 0);
		if (WIFEXITED(statuses[i]))
			statuses[i] = WEXITSTATUS(statuses[i]);
		else
			statuses[i] = 1;
		i++;
	}
	final_status = statuses[cmd_count - 1];
	free(statuses);
	free(pids);
	free(pipes);
	return (final_status);
}

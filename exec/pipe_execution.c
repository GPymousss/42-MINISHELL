/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 02:00:44 by gletilly          #+#    #+#             */
/*   Updated: 2025/08/25 13:47:00 by llangana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "../builtins/builtins.h"

void	close_all_pipes(int **pipes, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count - 1)
	{
		if (pipes[i])
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
			free(pipes[i]);
		}
		i++;
	}
	free(pipes);
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
	int	exit_status;

	setup_child_signals();
	setup_child_pipes(data->pipes, data->cmd_index, data->cmd_count);
	if (apply_redirections(shell, cmd) == -1)
		exit(1);
	if (is_builtin(cmd->args[0]))
	{
		exit_status = execute_builtin(shell, cmd);
		free_shell(shell);
		exit(exit_status);
	}
	else
	{
		exit_status = execute_external_cmd(shell, cmd);
		free_shell(shell);
		exit(exit_status);
	}
}

static int	process_child_status(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
		return (128 + WTERMSIG(status));
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	wait_for_pipeline(pid_t *pids, int **pipes, int cmd_count)
{
	int	*statuses;
	int	i;
	int	final_status;

	close_all_pipes(pipes, cmd_count);
	setup_signals_exec();
	statuses = malloc(sizeof(int) * cmd_count);
	if (!statuses)
	{
		free(pids);
		return (1);
	}
	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &statuses[i], 0);
		statuses[i] = process_child_status(statuses[i]);
		i++;
	}
	setup_signals();
	final_status = statuses[cmd_count - 1];
	free(statuses);
	free(pids);
	return (final_status);
}

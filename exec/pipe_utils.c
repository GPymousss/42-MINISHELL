/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 01:59:50 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/15 05:55:07 by llangana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	count_commands(t_cmd *cmds)
{
	int		count;
	t_cmd	*current;

	count = 0;
	current = cmds;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static void	close_pipes(int **pipes, int cmd_count)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < cmd_count)
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

static int	**create_pipes(int cmd_count)
{
	int	**pipes;
	int	i;

	if (cmd_count <= 1)
		return (NULL);
	pipes = malloc(sizeof(int *) * (cmd_count - 1));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < cmd_count - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) == -1)
		{
			close_pipes(pipes, i);
			free(pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

static int	fork_pipeline_commands(t_shell *shell, t_cmd *cmds,
		int **pipes, pid_t *pids)
{
	t_cmd			*current;
	t_pipe_data		data;
	int				cmd_count;

	cmd_count = count_commands(cmds);
	current = cmds;
	data.pipes = pipes;
	data.cmd_count = cmd_count;
	data.cmd_index = 0;
	while (current && data.cmd_index < cmd_count)
	{
		pids[data.cmd_index] = fork();
		if (pids[data.cmd_index] == 0)
			execute_pipe_child(shell, current, &data);
		current = current->next;
		data.cmd_index++;
	}
	return (cmd_count);
}

int	execute_pipeline(t_shell *shell, t_cmd *cmds)
{
	int		cmd_count;
	int		**pipes;
	pid_t	*pids;

	cmd_count = count_commands(cmds);
	if (cmd_count == 1)
		return (execute_single_cmd(shell, cmds));
	pipes = create_pipes(cmd_count);
	if (!pipes)
		return (1);
	pids = malloc(sizeof(pid_t) * cmd_count);
	if (!pids)
		return (close_pipes(pipes, cmd_count), 1);
	fork_pipeline_commands(shell, cmds, pipes, pids);
	return (wait_for_pipeline(pids, pipes, cmd_count));
}

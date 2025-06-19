/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <gletilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:25:32 by gletilly          #+#    #+#             */
/*   Updated: 2025/05/27 20:55:00 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	redir_cmd_input_output(t_shell *shell)
{
	char		*heredoc_name;
	t_symbol	type_redir;
	int			i;

	i = 0;
	heredoc_name = NULL;
	while (shell->cmd->redir != NULL)
	{
		type_redir = shell->cmd->redir->symbol;
		if (type_redir == REDIR_IN)
			redir_infile(shell);
		else if (type_redir == REDIR_OUT || type_redir == APPEND)
			redir_outfile(shell);
		else if (type_redir == HERE_DOC)
		{
			heredoc_name = here_doc(shell, i);
			if (heredoc_name)
				unlink(heredoc_name);
			i++;
		}
		shell->cmd->redir = shell->cmd->redir->next;
	}
}

void	ft_dup(t_shell *shell, t_pipe *pipex, char *command_path)
{
	if (dup_pipe(shell, pipex) == -1)
	{
		printf("error dup_pipe\n");
		free_all(shell, pipex);
		free(command_path);
		exit(1);
	}
	if (pipex->in_fd != -1)
		close(pipex->in_fd);
	close(pipex->fdpipe[0]);
	close(pipex->fdpipe[1]);
}

int	dup_pipe(t_shell *shell, t_pipe *pipex)
{
	int	p;

	p = pipex->pipe_index;
	if (p == FIRST_PIPE)
	{
		if (dup2(pipex->fdpipe[1], STDOUT_FILENO) == -1)
			return (-1);
	}
	else if (p == N_PIPE)
	{
		if (shell->fd_in == STDIN_FILENO)
			if (dup2(pipex->in_fd, STDIN_FILENO) == -1)
				return (-1);
		if (shell->fd_out == STDOUT_FILENO)
			if (dup2(pipex->fdpipe[1], STDOUT_FILENO) == -1)
				return (-1);
	}
	else if (p == LAST_PIPE)
	{
		if (dup2(pipex->in_fd, STDIN_FILENO) == -1)
			return (-1);
	}
	return (0);
}

void	ft_dup_redir(t_shell *shell)
{
	if (shell->fd_in != STDIN_FILENO)
	{
		dup2(shell->fd_in, STDIN_FILENO);
		close(shell->fd_in);
	}
	if (shell->fd_out != STDOUT_FILENO)
	{
		dup2(shell->fd_out, STDOUT_FILENO);
		close(shell->fd_out);
	}
}

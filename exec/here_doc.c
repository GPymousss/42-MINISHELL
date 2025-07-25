/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 02:19:54 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/10 07:35:54 by llangana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	check_delimiter(char *line, char *delimiter)
{
	size_t	delimiter_len;

	if (!line)
		return (1);
	delimiter_len = ft_strlen(delimiter);
	if (ft_strncmp(line, delimiter, delimiter_len) == 0
		&& ft_strlen(line) == delimiter_len)
		return (1);
	return (0);
}

static int	read_heredoc_lines(int write_fd, char *delimiter)
{
	char	*line;

	setup_signals_heredoc();
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: warning: ", STDERR_FILENO);
			ft_putendl_fd("here-document delimited by end-of-file",
				STDERR_FILENO);
			break ;
		}
		if (check_delimiter(line, delimiter))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, write_fd);
		free(line);
	}
	return (0);
}

static int	setup_heredoc_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

static int	redirect_heredoc_input(int read_fd)
{
	if (dup2(read_fd, STDIN_FILENO) == -1)
	{
		close(read_fd);
		perror("dup2");
		return (-1);
	}
	close(read_fd);
	return (0);
}

int	handle_heredoc_redirection(char *delimiter)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	if (setup_heredoc_pipe(pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (close(pipe_fd[0]), close(pipe_fd[1]), -1);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		read_heredoc_lines(pipe_fd[1], delimiter);
		close(pipe_fd[1]);
		exit(0);
	}
	close(pipe_fd[1]);
	setup_signals_exec();
	waitpid(pid, &status, 0);
	setup_signals();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (close(pipe_fd[0]), -1);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		return (close(pipe_fd[0]), -1);
	return (redirect_heredoc_input(pipe_fd[0]));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 05:22:53 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/10 05:22:53 by gletilly         ###   ########.fr       */
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
	int	pipe_fd[2];

	if (setup_heredoc_pipe(pipe_fd) == -1)
		return (-1);
	read_heredoc_lines(pipe_fd[1], delimiter);
	close(pipe_fd[1]);
	return (redirect_heredoc_input(pipe_fd[0]));
}

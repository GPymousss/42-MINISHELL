/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 02:19:27 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/08 02:19:27 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	handle_input_redirection(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(filename);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		perror("dup2");
		return (-1);
	}
	close(fd);
	return (0);
}

static int	handle_output_redirection(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(filename);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		perror("dup2");
		return (-1);
	}
	close(fd);
	return (0);
}

static int	handle_append_redirection(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(filename);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		perror("dup2");
		return (-1);
	}
	close(fd);
	return (0);
}

int	apply_single_redirection(t_redir *redir)
{
	if (redir->symbol == REDIR_IN)
		return (handle_input_redirection(redir->file));
	else if (redir->symbol == REDIR_OUT)
		return (handle_output_redirection(redir->file));
	else if (redir->symbol == APPEND)
		return (handle_append_redirection(redir->file));
	else if (redir->symbol == HERE_DOC)
		return (handle_heredoc_redirection(redir->file));
	return (-1);
}

int	apply_redirections(t_cmd *cmd)
{
	t_redir	*current;

	if (!cmd)
		return (0);
	current = cmd->redir;
	while (current)
	{
		if (apply_single_redirection(current) == -1)
			return (-1);
		current = current->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 06:28:32 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/10 06:28:32 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	open_input_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	}
	return (fd);
}

static int	open_output_file(char *filename, t_symbol symbol)
{
	int	fd;

	if (symbol == APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	}
	return (fd);
}

static int	handle_redirection_type(t_redir *redir)
{
	int	fd;

	if (redir->symbol == REDIR_IN)
	{
		fd = open_input_file(redir->file);
		if (fd != -1)
			dup2(fd, STDIN_FILENO);
	}
	else if (redir->symbol == REDIR_OUT || redir->symbol == APPEND)
	{
		fd = open_output_file(redir->file, redir->symbol);
		if (fd != -1)
			dup2(fd, STDOUT_FILENO);
	}
	if (fd != -1)
		close(fd);
	if (fd != -1)
		return (0);
	return (1);
}

int	setup_redirections(t_redir *redirs)
{
	t_redir	*current;
	int		has_error;

	current = redirs;
	has_error = 0;
	while (current)
	{
		if (handle_redirection_type(current) != 0)
		{
			has_error = 1;
			return (1);
		}
		current = current->next;
	}
	return (has_error);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:26:31 by llangana          #+#    #+#             */
/*   Updated: 2025/09/05 16:28:53 by llangana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	prepare_heredocs(t_shell *shell, t_cmd *cmds)
{
	t_cmd	*current;
	t_redir	*redir;
	int		status;

	current = cmds;
	while (current)
	{
		redir = current->redir;
		while (redir)
		{
			if (redir->symbol == HERE_DOC)
			{
				status = handle_heredoc_redirection(shell, redir->file);
				if (status == -1)
					return (130);
			}
			redir = redir->next;
		}
		current = current->next;
	}
	return (0);
}

int	heredoc_failed(int status)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (1);
	if (WIFEXITED(status) && (WEXITSTATUS(status) == 1
			|| WEXITSTATUS(status) == 130))
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 04:38:27 by gletilly          #+#    #+#             */
/*   Updated: 2025/08/04 12:50:08 by llangana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	handle_exec_error(char *cmd, int error_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	if (error_code == CMD_NOT_FOUND)
		ft_putendl_fd(": command not found", STDERR_FILENO);
	else if (error_code == PERMISSION_DENIED)
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	else
		ft_putendl_fd(": unknown error", STDERR_FILENO);
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

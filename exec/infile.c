/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <gletilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:28:14 by gletilly          #+#    #+#             */
/*   Updated: 2025/05/27 13:52:31 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	redir_infile(t_shell *shell)
{
	int		fd;
	char	*str;

	str = shell->cmd->redir->str;
	if (access(str, F_OK) != 0)
		(perror("File not accessible"), exit(EXIT_FAILURE));
	else if (access(str, R_OK) != 0)
	{
		perror("File not readable");
		exit(EXIT_FAILURE);
	}
	fd = open(str, O_RDWR);
	if (fd == -1)
	{
		perror("Cannot open file");
		exit(EXIT_FAILURE);
	}
	if (shell->fd_in != STDIN_FILENO)
	{
		close(shell->fd_in);
		shell->fd_in = fd;
	}
	else
		shell->fd_in = fd;
}

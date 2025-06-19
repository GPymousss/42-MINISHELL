/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <gletilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:26:15 by gletilly          #+#    #+#             */
/*   Updated: 2025/05/27 20:55:37 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_pipe	*set_struct_pipex(t_shell *shell)
{
	t_pipe	*pipex;

	pipex = init_struct_pipex();
	if (!pipex)
	{
		printf("Error alloc pipex");
		free_all(shell, pipex);
		exit(EXIT_FAILURE);
	}
	return (pipex);
}

char	*find_command_exist_executable(t_shell *shell, t_pipe *pipex)
{
	char	*command_path;

	command_path = check_command_path(shell->cmd->cmd[0], shell->envp);
	if (command_path == NULL)
	{
		printf("bash: %s: command not found\n", shell->cmd->cmd[0]);
		free_all(shell, pipex);
		exit(127);
	}
	else
		return (command_path);
}

int	ft_wait(t_shell *shell, pid_t *id_fork, size_t nb_pipes)
{
	size_t	i;

	i = 0;
	while (i < nb_pipes + 1)
	{
		if (waitpid(id_fork[i], &shell->wstatus, 0) == -1)
		{
			perror("waitpid error");
			exit(1);
		}
		i++;
	}
	return (shell->wstatus);
}

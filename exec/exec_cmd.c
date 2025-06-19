/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <gletilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:24:01 by gletilly          #+#    #+#             */
/*   Updated: 2025/05/27 20:54:52 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_cmd(t_shell *shell)
{
	t_pipe	*pipex;
	pid_t	*id_fork;

	if (shell->nb_pipe != 0)
		pipex = set_struct_pipex(shell);
	else
		pipex = NULL;
	id_fork = fork_cmd(shell, pipex);
	shell->wstatus = ft_wait(shell, id_fork, shell->nb_pipe);
	if (WIFEXITED(shell->wstatus) && WEXITSTATUS(shell->wstatus))
		return (WEXITSTATUS(shell->wstatus));
	free(id_fork);
	free(pipex);
	return (0);
}

pid_t	*fork_cmd(t_shell *shell, t_pipe *pipex)
{
	size_t	nb_fork;
	pid_t	*id_fork;

	if (shell->nb_pipe == 0)
		nb_fork = 1;
	else
		nb_fork = shell->nb_pipe + 1;
	id_fork = malloc(sizeof(pid_t) * (nb_fork + 1));
	id_fork[nb_fork] = 0;
	if (!id_fork)
	{
		printf("Error malloc id_fork");
		free_all(shell, pipex);
	}
	else
		create_children(shell, id_fork, pipex);
	return (id_fork);
}

void	create_children(t_shell *shell, pid_t *id_fork, t_pipe *pipex)
{
	size_t	i;

	i = 0;
	while (shell->cmd != NULL)
	{
		if (shell->nb_pipe > 0)
			if (pipe(pipex->fdpipe) == -1)
				(free_all(shell, pipex), exit(EXIT_FAILURE));
		id_fork[i] = fork();
		if (id_fork[i] == -1)
		{
			printf("Error fork id_fork[%zu]", i);
			(free(id_fork), free_all(shell, pipex));
		}
		else if (id_fork[i] == 0)
			create_child(shell, pipex);
		if (shell->nb_pipe > 0)
			pipe_struct_update(shell, pipex, i);
		shell->cmd = shell->cmd->next;
		i++;
	}
}

void	create_child(t_shell *shell, t_pipe *pipex)
{
	char	*command_path;
	bool	is_built_ins;

	is_built_ins = is_cmd_built_ins(shell);
	if (!is_built_ins)
		command_path = find_command_exist_executable(shell, pipex);
	redir_cmd_input_output(shell);
	ft_dup_redir(shell);
	if (shell->nb_pipe != 0)
		ft_dup(shell, pipex, command_path);
	if (is_built_ins)
	{
		exec_built_in(shell);
		exit(shell->wstatus);
	}
	else if (execve(command_path, &shell->cmd->cmd[0], shell->envp) == -1)
	{
		perror("ERROR EXEC VE");
		free_all(shell, pipex);
		free(command_path);
		exit(126);
	}
}

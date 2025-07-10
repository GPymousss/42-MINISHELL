/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 04:37:26 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/10 07:34:03 by llangana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	handle_child_process(t_shell *shell, t_cmd *cmd, char *cmd_path)
{
	if (execve(cmd_path, cmd->args, shell->envp) == -1)
	{
		handle_exec_error(cmd->args[0], PERMISSION_DENIED);
		free(cmd_path);
		exit(PERMISSION_DENIED);
	}
	return (0);
}

static void	print_error_message(char *cmd, int error_code, int is_dir)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	if (error_code == PERMISSION_DENIED && is_dir)
		ft_putendl_fd(": Is a directory", STDERR_FILENO);
	else if (error_code == PERMISSION_DENIED)
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	else if (ft_strchr(cmd, '/'))
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	else
		ft_putendl_fd(": command not found", STDERR_FILENO);
}

int	execute_external_cmd(t_shell *shell, t_cmd *cmd)
{
	char	*cmd_path;
	pid_t	pid;
	int		status;
	int		error_code;
	int		is_dir;

	cmd_path = find_command_path_with_error(cmd->args[0], shell->envp,
			&error_code, &is_dir);
	if (!cmd_path)
	{
		print_error_message(cmd->args[0], error_code, is_dir);
		return (error_code);
	}
	pid = fork();
	if (pid == -1)
	{
		(perror("fork"), free(cmd_path));
		return (1);
	}
	if (pid == 0)
		handle_child_process(shell, cmd, cmd_path);
	(free(cmd_path), waitpid(pid, &status, 0));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

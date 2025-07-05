/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 04:37:06 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/05 04:37:06 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"

int	exec(t_shell *shell)
{
	t_cmd	*current;
	int		last_exit_status;

	if (!shell || !shell->cmds)
		return (1);
	current = shell->cmds;
	last_exit_status = 0;
	while (current)
	{
		if (!current->args || !current->args[0])
		{
			current = current->next;
			continue ;
		}
		last_exit_status = execute_single_cmd(shell, current);
		shell->exit_status = last_exit_status;
		current = current->next;
	}
	return (last_exit_status);
}

int	execute_single_cmd(t_shell *shell, t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (is_builtin(cmd->args[0]))
		return (execute_builtin(shell, cmd));
	return (execute_external_cmd(shell, cmd));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:17:06 by lomont            #+#    #+#             */
/*   Updated: 2025/07/05 23:17:17 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->input)
		free(shell->input);
	if (shell->tokens)
		free_tokens(shell->tokens);
	if (shell->cmds)
		free_cmds(shell->cmds);
	if (shell->env)
		free_envp_struct(shell->env);
	if (shell->envp)
		free_array(shell->envp);
	if (shell->stdin_backup != -1)
		close(shell->stdin_backup);
	if (shell->stdout_backup != -1)
		close(shell->stdout_backup);
	free(shell);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 05:21:21 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/10 05:21:21 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_env(t_shell *shell, t_cmd *cmd)
{
	int	i;

	(void)cmd;
	if (!shell->envp)
		return (1);
	i = 0;
	while (shell->envp[i])
	{
		ft_putendl_fd(shell->envp[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}

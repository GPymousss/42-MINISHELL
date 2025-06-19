/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:04:56 by gletilly          #+#    #+#             */
/*   Updated: 2025/06/13 16:40:16 by llangana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"

void	echo_w_arg(t_shell *shell)
{
	int	i;

	i = 1;
	while (shell->cmd->cmd[++i])
	{
		if (shell->cmd->cmd[i + 1] == NULL)
			printf("%s", shell->cmd->cmd[i]);
		else
			printf("%s ", shell->cmd->cmd[i]);
	}
}

int	ft_echo(t_shell *shell)
{
	bool	has_n;
	int		i;
	int		start;

	if (!shell->cmd->cmd[1])
		return (printf("\n"), 0);
	has_n = (ft_strncmp(shell->cmd->cmd[1], "-n", 3) == 0);
	start = has_n + 1;
	i = start;
	while (shell->cmd->cmd[i])
	{
		printf("%s", shell->cmd->cmd[i]);
		if (shell->cmd->cmd[++i])
			printf(" ");
	}
	if (!has_n)
		printf("\n");
	return (0);
}

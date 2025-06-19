/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:17:06 by lomont            #+#    #+#             */
/*   Updated: 2025/06/14 12:44:33 by llangana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->cmd)
	{
		free_cmd_struct(shell->cmd);
		shell->cmd = NULL;
	}
}

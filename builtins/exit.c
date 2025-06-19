/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:05:02 by gletilly          #+#    #+#             */
/*   Updated: 2025/06/15 11:02:42 by llangana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"

void	ft_exit(t_shell *shell)
{
	ft_putstr_fd("exit\n", 1);
	free_shell(shell);
	rl_clear_history();
	exit(shell->wstatus);
}

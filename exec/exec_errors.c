/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 05:22:27 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/10 05:22:27 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	handle_exec_error(char *cmd, int error_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	if (error_code == CMD_NOT_FOUND)
		ft_putendl_fd(": command not found", STDERR_FILENO);
	else if (error_code == PERMISSION_DENIED)
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	else
		ft_putendl_fd(": unknown error", STDERR_FILENO);
}

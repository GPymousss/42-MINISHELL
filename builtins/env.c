/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <gletilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:04:53 by gletilly          #+#    #+#             */
/*   Updated: 2025/05/27 21:12:44 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"

int	ft_env(t_shell *shell)
{
	if (!shell->envp)
	{
		perror("env");
		return (1);
	}
	else
		print_array(shell->envp);
	return (0);
}

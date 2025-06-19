/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <gletilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:52:56 by gletilly          #+#    #+#             */
/*   Updated: 2025/05/27 20:53:37 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	free_all(t_shell *shell, t_pipe *pipex)
{
	free_shell(shell);
	if (pipex)
		free(pipex);
	exit(EXIT_FAILURE);
}

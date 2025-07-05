/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:52:56 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/04 23:12:45 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	free_all(t_shell *shell)
{
	if (!shell)
		return ;
	free_shell(shell);
	exit(EXIT_FAILURE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_envp_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:36:53 by llangana          #+#    #+#             */
/*   Updated: 2025/06/14 11:44:36 by llangana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	free_envp_struct(t_envp *env)
{
	t_envp	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->envp);
		free(tmp);
	}
}

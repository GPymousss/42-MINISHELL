/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_envp_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:36:53 by llangana          #+#    #+#             */
/*   Updated: 2025/08/04 23:10:17 by llangana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
void	free_envp_struct(t_envp *env)
{
	t_envp	*tmp;

	while (env)
	{
		tmp = env->next;
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
		env = tmp;
	}
}
*/

void	free_env(t_envp *env)
{
	t_envp	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	free_pipe_data(t_pipe_data *data)
{
	int	i;

	if (!data || !data->pipes)
		return ;
	i = 0;
	while (i < data->cmd_count - 1)
	{
		if (data->pipes[i])
		{
			close(data->pipes[i][0]);
			close(data->pipes[i][1]);
			free(data->pipes[i]);
		}
		i++;
	}
	free(data->pipes);
	data->pipes = NULL;
}

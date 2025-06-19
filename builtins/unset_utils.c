/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:00:00 by gletilly          #+#    #+#             */
/*   Updated: 2025/06/19 12:00:00 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"

static void	ft_free_envp_list(t_envp *env)
{
	t_envp	*tmp;

	while (env)
	{
		tmp = env->next;
		if (env->envp)
			free(env->envp);
		free(env);
		env = tmp;
	}
}

static void	ft_free_old_envp(char **envp)
{
	size_t	j;

	if (envp)
	{
		j = 0;
		while (envp[j])
		{
			free(envp[j]);
			j++;
		}
		free(envp);
	}
}

void	ft_unset_var(t_shell *shell, char *name_to_unset)
{
	char	**tmp;
	t_envp	*env;

	env = NULL;
	env = fill_envp(env, shell->envp);
	if (!env)
		return ;
	env = ft_delone_env(env, name_to_unset);
	tmp = shell->envp;
	shell->envp = ft_convert_node_to_envp(env);
	if (!shell->envp)
	{
		shell->envp = tmp;
		ft_free_envp_list(env);
		return ;
	}
	ft_free_old_envp(tmp);
	ft_free_envp_list(env);
}

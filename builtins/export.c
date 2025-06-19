/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:05:11 by gletilly          #+#    #+#             */
/*   Updated: 2025/06/15 01:29:21 by llangana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"

int	ft_export(t_shell *shell)
{
	size_t	i;
	int		exit_code;

	i = 1;
	exit_code = 0;
	if (shell->cmd->cmd[i] == 0)
		export_all(shell->envp);
	while (shell->cmd->cmd[i])
	{
		if (check_arg_export_syntax(shell->cmd->cmd[i]) == true)
			export_arg_to_env(shell, shell->cmd->cmd[i]);
		else
			exit_code = 1;
		i++;
	}
	return (exit_code);
}

static char	**duplicate_env(char **envp)
{
	char	**new_env;
	int		count;
	int		i;

	if (!envp)
		return (NULL);
	count = 0;
	while (envp[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
			return (free_array_partial(new_env, i));
		i++;
	}
	new_env[count] = NULL;
	return (new_env);
}

static bool	init_env_once(t_shell *shell)
{
	char	**tmp;

	tmp = duplicate_env(shell->envp);
	if (!tmp)
	{
		ft_putstr_fd("minishell: export: memory error\n", 2);
		return (false);
	}
	shell->envp = tmp;
	return (true);
}

void	export_arg_to_env(t_shell *shell, char *arg)
{
	static bool	first_export;
	t_envp		*new_envp;
	t_envp		*env;
	char		**tmp;
	char		*new_arg;

	first_export = true;
	if (first_export)
	{
		if (!init_env_once(shell))
			return ;
		first_export = false;
	}
	env = NULL;
	new_arg = remove_extra_char_before_egal(arg);
	new_envp = create_node_envp(new_arg);
	env = fill_envp(env, shell->envp);
	ft_add_back_envp(&env, new_envp);
	tmp = shell->envp;
	shell->envp = ft_convert_node_to_envp(env);
	free_array(tmp);
	free_envp_struct(env);
	free(new_arg);
}

void	export_all(char **envp)
{
	size_t	i;
	size_t	k;

	i = 0;
	while (envp[i])
	{
		k = 0;
		ft_putstr_fd("export ", 1);
		while (envp[i][k])
		{
			if (k > 0)
				if (envp[i][k - 1] == '=')
					ft_putchar_fd('"', 1);
			ft_putchar_fd(envp[i][k], 1);
			k++;
		}
		ft_putstr_fd("\"\n", 1);
		i++;
	}
}

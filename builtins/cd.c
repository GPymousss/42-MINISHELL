/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:04:28 by gletilly          #+#    #+#             */
/*   Updated: 2025/06/15 10:58:07 by llangana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"

int	exec_cd(char *arg)
{
	if (chdir(arg) == -1)
	{
		perror("cd");
		return (1);
	}
	else
	{
		printf("Success! You changed the directory\n");
		return (0);
	}
}

int	ft_cd(t_shell *shell)
{
	char	*arg;

	if (shell->cmd->cmd[1] == NULL)
	{
		arg = get_specific_env(shell->envp, "HOME");
		return (exec_cd(arg));
	}
	if (check_arg_nbr(shell) == -1)
		return (1);
	arg = get_cd_argument(shell->cmd->cmd[1], shell->envp);
	if (arg == NULL)
		return (1);
	else
	{
		exec_cd(arg);
		if (ft_strncmp(shell->cmd->cmd[1], "-\0", 2) == 0)
			ft_pwd(true);
		update_pwd(shell, arg);
		return (0);
	}
}

void	find_change_env(t_envp *env, char *new_env, char *env_to_replace)
{
	while (env)
	{
		if (ft_strncmp(env->envp, env_to_replace,
				ft_strlen(env_to_replace)) == 0)
		{
			env->envp = new_env;
			break ;
		}
		env = env->next;
	}
}

void	update_pwd(t_shell *shell, char *arg)
{
	char	*oldpwd;
	char	*oldpwd_tmp;
	char	*new_env;
	char	**tmp;
	t_envp	*env;

	env = NULL;
	oldpwd_tmp = get_specific_env(shell->envp, "PWD=");
	oldpwd = ft_substr(oldpwd_tmp, 0, ft_strlen(oldpwd_tmp));
	free(oldpwd_tmp);
	oldpwd_tmp = ft_strjoin("OLDPWD=", oldpwd);
	free(oldpwd);
	new_env = ft_strjoin("PWD=", arg);
	env = fill_envp(env, shell->envp);
	find_change_env(env, new_env, "PWD");
	find_change_env(env, oldpwd_tmp, "OLDPWD");
	tmp = shell->envp;
	shell->envp = ft_convert_node_to_envp(env);
	free(new_env);
	free(tmp);
}

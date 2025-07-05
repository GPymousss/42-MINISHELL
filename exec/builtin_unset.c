/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 05:30:00 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/05 05:30:00 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_valid_unset_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	remove_env_node(t_shell *shell, char *key)
{
	t_envp	*current;
	t_envp	*prev;

	if (!shell->env)
		return ;
	if (ft_strcmp(shell->env->key, key) == 0)
	{
		current = shell->env;
		shell->env = shell->env->next;
		(free(current->key), free(current->value), free(current));
		return ;
	}
	prev = shell->env;
	current = shell->env->next;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			prev->next = current->next;
			(free(current->key), free(current->value), free(current));
			return ;
		}
		prev = current;
		current = current->next;
	}
}

static int	process_unset_argument(t_shell *shell, char *var_name)
{
	if (!is_valid_unset_identifier(var_name))
	{
		ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
		ft_putstr_fd(var_name, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return (1);
	}
	remove_env_node(shell, var_name);
	rebuild_envp_array(shell);
	return (0);
}

int	builtin_unset(t_shell *shell, t_cmd *cmd)
{
	int	i;
	int	exit_status;

	if (!shell || !cmd || !cmd->args)
		return (1);
	if (!cmd->args[1])
		return (0);
	exit_status = 0;
	i = 1;
	while (cmd->args[i])
	{
		if (process_unset_argument(shell, cmd->args[i]) != 0)
			exit_status = 1;
		i++;
	}
	return (exit_status);
}

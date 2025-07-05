/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 23:00:03 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/05 23:00:03 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_envp	*create_env_node(char *key, char *value)
{
	t_envp	*new_node;

	new_node = malloc(sizeof(t_envp));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}

static void	add_env_to_list(t_shell *shell, char *key, char *value)
{
	t_envp	*new_node;
	t_envp	*current;

	new_node = create_env_node(key, value);
	if (!new_node)
		return ;
	if (!shell->env)
	{
		shell->env = new_node;
		return ;
	}
	current = shell->env;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

static void	parse_env_string(t_shell *shell, char *env_str)
{
	char	*equal_pos;
	char	*key;
	char	*value;

	equal_pos = ft_strchr(env_str, '=');
	if (!equal_pos)
		return ;
	key = ft_substr(env_str, 0, equal_pos - env_str);
	value = equal_pos + 1;
	add_env_to_list(shell, key, value);
	free(key);
}

static char	**copy_envp(char **envp)
{
	char	**new_envp;
	int		count;
	int		i;

	count = 0;
	while (envp[count])
		count++;
	new_envp = malloc(sizeof(char *) * (count + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;
	int		i;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->input = NULL;
	shell->tokens = NULL;
	shell->cmds = NULL;
	shell->env = NULL;
	shell->envp = NULL;
	shell->exit_status = 0;
	shell->stdin_backup = dup(STDIN_FILENO);
	shell->stdout_backup = dup(STDOUT_FILENO);
	if (!envp)
		return (shell);
	i = 0;
	while (envp[i])
	{
		parse_env_string(shell, envp[i]);
		i++;
	}
	shell->envp = copy_envp(envp);
	return (shell);
}

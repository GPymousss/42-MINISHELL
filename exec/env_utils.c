/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 05:30:00 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/05 05:30:00 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_envp	*find_env_node(t_envp *env, char *key)
{
	t_envp	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	update_env_node(t_envp *node, char *new_value)
{
	if (!node || !new_value)
		return ;
	if (node->value)
		free(node->value);
	node->value = ft_strdup(new_value);
}

t_envp	*create_env_node(char *key, char *value)
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

void	add_env_node(t_shell *shell, char *key, char *value)
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

static int	count_env_nodes(t_envp *env)
{
	int		count;
	t_envp	*current;

	count = 0;
	current = env;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	rebuild_envp_array(t_shell *shell)
{
	t_envp	*current;
	char	**new_envp;
	char	*temp;
	int		count;
	int		i;

	count = count_env_nodes(shell->env);
	if (shell->envp)
		free_array(shell->envp);
	new_envp = malloc(sizeof(char *) * (count + 1));
	if (!new_envp)
		return ;
	current = shell->env;
	i = 0;
	while (current)
	{
		temp = ft_strjoin(current->key, "=");
		new_envp[i] = ft_strjoin_free(temp, ft_strdup(current->value));
		current = current->next;
		i++;
	}
	new_envp[i] = NULL;
	shell->envp = new_envp;
}

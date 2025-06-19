/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:09:42 by gletilly          #+#    #+#             */
/*   Updated: 2025/06/19 09:32:24 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_envp	*ft_last_envp(t_envp *lst)
{
	t_envp	*tmp;

	if (lst == NULL)
		return (lst);
	while (lst != NULL)
	{
		tmp = lst;
		lst = lst->next;
	}
	return (tmp);
}

void	ft_add_back_envp(t_envp **lst, t_envp *new)
{
	t_envp	*current;

	if (*lst == NULL)
		*lst = new;
	else
	{
		current = ft_last_envp(*lst);
		current->next = new;
	}
}

t_envp	*create_node_envp(char *env)
{
	t_envp	*new_env;

	new_env = malloc(sizeof(*new_env));
	if (!new_env)
		return (NULL);
	new_env->envp = ft_strdup(env);
	new_env->next = NULL;
	return (new_env);
}

t_envp	*fill_envp(t_envp *node, char **envp)
{
	t_envp	*new_node;
	size_t	i;
	t_envp	*head;

	if (!envp)
		return (NULL);
	head = node;
	i = 0;
	while (envp[i])
	{
		new_node = create_node_envp(envp[i]);
		if (!new_node)
		{
			free_envp_struct(head);
			return (NULL);
		}
		if (!head)
			head = new_node;
		else
			ft_add_back_envp(&head, new_node);
		i++;
	}
	return (head);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:05:25 by gletilly          #+#    #+#             */
/*   Updated: 2025/06/19 09:33:31 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"

t_envp	*ft_delone_env(t_envp *lst, char *env_to_find)
{
	t_envp	*current;
	t_envp	*previous;
	size_t	len;

	if (!lst || !env_to_find)
		return (lst);
	len = ft_strlen(env_to_find);
	current = lst;
	previous = NULL;
	while (current != NULL)
	{
		if (ft_strncmp(current->envp, env_to_find, len) == 0
			&& (current->envp[len] == '=' || current->envp[len] == '\0'))
		{
			if (previous == NULL)
				lst = current->next;
			else
				previous->next = current->next;
			(free(current->envp), free(current));
			break ;
		}
		previous = current;
		current = current->next;
	}
	return (lst);
}

bool	check_if_in_envp(char **envp, char *str)
{
	size_t	i;
	size_t	len;

	if (!envp || !str)
		return (false);
	len = ft_strlen(str);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], str, len) == 0
			&& (envp[i][len] == '=' || envp[i][len] == '\0'))
			return (true);
		i++;
	}
	return (false);
}

int	ft_unset(t_shell *shell)
{
	size_t	i;

	if (!shell || !shell->cmd || !shell->cmd->cmd)
		return (1);
	i = 1;
	while (shell->cmd->cmd[i] != NULL)
	{
		if (check_if_in_envp(shell->envp, shell->cmd->cmd[i]) == true)
			ft_unset_var(shell, shell->cmd->cmd[i]);
		i++;
	}
	return (0);
}

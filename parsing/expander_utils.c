/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:28:46 by llangana          #+#    #+#             */
/*   Updated: 2025/07/08 02:39:11 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_env_value(char **envp, const char *name)
{
	size_t	name_len;
	char	*env;
	char	*value;
	int		i;

	if (!name || !envp)
		return (NULL);
	name_len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		env = envp[i];
		if (ft_strncmp(env, name, name_len) == 0 && env[name_len] == '=')
		{
			value = ft_strchr(env, '=');
			if (value)
				return (ft_strdup(value + 1));
		}
		i++;
	}
	return (NULL);
}

static char	*get_env_from_list(t_envp *env, const char *name)
{
	t_envp	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, name) == 0)
		{
			if (current->value)
				return (ft_strdup(current->value));
			return (ft_strdup(""));
		}
		current = current->next;
	}
	return (NULL);
}

char	*expand_variable(t_shell *shell, const char *str, int *i)
{
	int		start;
	char	*name;
	char	*val;

	if (str[*i] == '?')
		return ((*i)++, ft_itoa(shell->exit_status));
	start = *i;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	if (*i == start)
		return (ft_strdup("$"));
	name = ft_substr(str, start, *i - start);
	if (!name)
		return (NULL);
	val = get_env_from_list(shell->env, name);
	free(name);
	if (!val)
		val = ft_strdup("");
	return (val);
}

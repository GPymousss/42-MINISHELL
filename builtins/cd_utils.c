/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 06:47:06 by gletilly          #+#    #+#             */
/*   Updated: 2025/06/19 09:30:40 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"

static int	count_envp_nodes(t_envp *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static char	**allocate_envp_array(int count)
{
	char	**final_envp;

	final_envp = malloc(sizeof(char *) * (count + 1));
	if (!final_envp)
		return (NULL);
	return (final_envp);
}

static void	free_partial_envp(char **envp, int i)
{
	while (--i >= 0)
		free(envp[i]);
	free(envp);
}

char	**ft_convert_node_to_envp(t_envp *env)
{
	char	**final_envp;
	t_envp	*current;
	int		count;
	int		i;

	if (!env)
		return (NULL);
	count = count_envp_nodes(env);
	final_envp = allocate_envp_array(count);
	if (!final_envp)
		return (NULL);
	current = env;
	i = 0;
	while (current && i < count)
	{
		final_envp[i] = ft_strdup(current->envp);
		if (!final_envp[i])
			return (free_partial_envp(final_envp, i), NULL);
		current = current->next;
		i++;
	}
	final_envp[count] = NULL;
	return (final_envp);
}

char	*get_cd_argument(char *cmd, char **envp)
{
	size_t	i;
	char	*arg;
	char	*new_arg;
	char	**arg_tab;

	i = 0;
	new_arg = NULL;
	if (ft_strchr(cmd, '/') != NULL)
	{
		arg_tab = ft_split(cmd, '/');
		while (arg_tab[i])
		{
			arg = check_arg(arg_tab[i], envp);
			new_arg = join_args(arg, new_arg);
			i++;
		}
		free_array(arg_tab);
	}
	else
		new_arg = check_arg(cmd, envp);
	return (new_arg);
}

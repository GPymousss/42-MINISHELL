/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 04:37:41 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/05 04:37:41 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*check_absolute_path(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (is_valid_command(cmd))
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (NULL);
}

static char	*search_in_paths(char *cmd, char **paths)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin_free(full_path, ft_strdup(cmd));
		if (is_valid_command(full_path))
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_command_path(char *cmd, char **envp)
{
	char	**paths;
	char	*result;
	char	*path_env;

	if (!cmd)
		return (NULL);
	result = check_absolute_path(cmd);
	if (result)
		return (result);
	path_env = get_path_env(envp);
	if (!path_env)
		return (NULL);
	paths = split_path(path_env);
	if (!paths)
		return (NULL);
	result = search_in_paths(cmd, paths);
	free_array(paths);
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 05:22:57 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/10 05:22:57 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	is_directory_check(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0)
		return ((path_stat.st_mode & 0170000) == 0040000);
	return (0);
}

static char	*check_absolute_path(char *cmd, int *error_code, int *is_dir)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) != 0)
		{
			*error_code = CMD_NOT_FOUND;
			*is_dir = 0;
			return (NULL);
		}
		if (is_directory_check(cmd))
		{
			*error_code = PERMISSION_DENIED;
			*is_dir = 1;
			return (NULL);
		}
		if (access(cmd, X_OK) != 0)
		{
			*error_code = PERMISSION_DENIED;
			*is_dir = 0;
			return (NULL);
		}
		return (ft_strdup(cmd));
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

char	*find_command_path_with_error(char *cmd, char **envp,
		int *error_code, int *is_dir)
{
	char	**paths;
	char	*result;
	char	*path_env;

	*error_code = CMD_NOT_FOUND;
	*is_dir = 0;
	if (!cmd)
		return (NULL);
	result = check_absolute_path(cmd, error_code, is_dir);
	if (result || *error_code == PERMISSION_DENIED)
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

char	*find_command_path(char *cmd, char **envp)
{
	int	error_code;
	int	is_dir;

	return (find_command_path_with_error(cmd, envp, &error_code, &is_dir));
}

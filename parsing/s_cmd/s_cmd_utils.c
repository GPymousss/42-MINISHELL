#include "../parsing.h"

char	*p_get_env_value(char *name, char **envp)
{
	int		i;
	size_t	len;

	if (!name || !envp)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (ft_strdup(envp[i] + len + 1));
		i++;
	}
	return (NULL);
}

char	*p_check_cmd_in_path(char *path, char *cmd)
{
	char	*full_path;
	char	*tmp;

	if (!path || !cmd)
		return (NULL);
	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!full_path)
		return (NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

bool	p_exec_cmd(t_cmd *cmd, char **envp)
{
	char	*path;

	if (!cmd || !cmd->cmd || !cmd->cmd[0] || !envp)
		return (false);
	if (p_process_redirections(cmd->redir, &STDIN_FILENO, &STDOUT_FILENO)
		== false)
		return (false);
	path = p_get_cmd_path(cmd->cmd[0], envp);
	if (!path)
	{
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putendl_fd(": command not found", 2);
		return (false);
	}
	execve(path, cmd->cmd, envp);
	perror("execve");
	free(path);
	return (false);
}

bool	p_cmd_is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (true);
	return (false);
}

bool	p_exec_builtin(t_cmd *cmd, t_shell *lst)
{
	if (!cmd || !cmd->cmd || !cmd->cmd[0] || !lst)
		return (false);
	if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		return (p_builtin_echo(cmd->cmd));
	else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		return (p_builtin_cd(cmd->cmd, lst));
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		return (p_builtin_pwd());
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		return (p_builtin_export(cmd->cmd, lst));
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		return (p_builtin_unset(cmd->cmd, lst));
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		return (p_builtin_env(lst->envp));
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		return (p_builtin_exit(cmd->cmd, lst));
	return (false);
}

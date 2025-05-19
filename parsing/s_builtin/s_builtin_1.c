#include "../parsing.h"

bool	p_builtin_echo(char **args)
{
	int	i;
	int	n_flag;

	if (!args || !args[0])
		return (false);
	n_flag = 0;
	i = 1;
	if (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		n_flag = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (true);
}

bool	p_builtin_cd(char **args, t_shell *lst)
{
	char	*path;
	char	cwd[PATH_MAX];

	if (!args || !args[0] || !lst)
		return (false);
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
		path = p_get_env_value("HOME", lst->envp);
	else if (ft_strcmp(args[1], "-") == 0)
		path = p_get_env_value("OLDPWD", lst->envp);
	else
		path = ft_strdup(args[1]);
	if (!path)
		return (false);
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		free(path);
		return (false);
	}
	if (chdir(path) == -1)
	{
		free(path);
		return (false);
	}
	free(path);
	return (true);
}

bool	p_builtin_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		perror("pwd");
		return (false);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	return (true);
}

bool	p_is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str)
		return (false);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (false);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

bool	p_builtin_export(char **args, t_shell *lst)
{
	int		i;
	char	*equal_pos;

	if (!args || !args[0] || !lst)
		return (false);
	if (!args[1])
		return (p_print_sorted_env(lst->envp));
	i = 1;
	while (args[i])
	{
		equal_pos = ft_strchr(args[i], '=');
		if (equal_pos)
			*equal_pos = '\0';
		if (p_is_valid_identifier(args[i]))
			p_set_env_var(lst, args[i], equal_pos ? equal_pos + 1 : NULL);
		else
		{
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd(": not a valid identifier", 2);
		}
		if (equal_pos)
			*equal_pos = '=';
		i++;
	}
	return (true);
}

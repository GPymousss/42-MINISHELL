#include "../parsing.h"

bool	p_print_sorted_env(char **envp)
{
	char	**sorted_env;
	char	*tmp;
	int		i;
	int		j;
	int		count;

	if (!envp)
		return (false);
	count = 0;
	while (envp[count])
		count++;
	sorted_env = malloc(sizeof(char *) * (count + 1));
	if (!sorted_env)
		return (false);
	i = 0;
	while (i < count)
	{
		sorted_env[i] = ft_strdup(envp[i]);
		i++;
	}
	sorted_env[count] = NULL;
	p_sort_env(sorted_env, count);
	p_print_export_format(sorted_env);
	p_free_split(sorted_env);
	return (true);
}

void	p_sort_env(char **env, int count)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
			{
				tmp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	p_print_export_format(char **env)
{
	int		i;
	char	*equal_pos;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		equal_pos = ft_strchr(env[i], '=');
		if (equal_pos)
		{
			*equal_pos = '\0';
			ft_putstr_fd(env[i], STDOUT_FILENO);
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(equal_pos + 1, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
			*equal_pos = '=';
		}
		else
			ft_putstr_fd(env[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

bool	p_set_env_var(t_shell *lst, char *name, char *value)
{
	int		i;
	int		count;
	char	*new_var;
	char	**new_envp;

	if (!lst || !name)
		return (false);
	i = p_find_env_var(lst->envp, name);
	if (i >= 0)
	{
		free(lst->envp[i]);
		if (value)
			lst->envp[i] = p_create_env_string(name, value);
		else
			lst->envp[i] = ft_strdup(name);
		return (lst->envp[i] != NULL);
	}
	new_var = value ? p_create_env_string(name, value) : ft_strdup(name);
	if (!new_var)
		return (false);
	new_envp = p_add_env_var(lst->envp, new_var);
	if (!new_envp)
	{
		free(new_var);
		return (false);
	}
	lst->envp = new_envp;
	return (true);
}

bool	p_builtin_unset(char **args, t_shell *lst)
{
	int	i;
	int	env_index;

	if (!args || !args[0] || !lst)
		return (false);
	i = 1;
	while (args[i])
	{
		if (p_is_valid_identifier(args[i]))
		{
			env_index = p_find_env_var(lst->envp, args[i]);
			if (env_index >= 0)
				p_remove_env_var(lst, env_index);
		}
		else
		{
			ft_putstr_fd("unset: ", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd(": not a valid identifier", 2);
		}
		i++;
	}
	return (true);
}

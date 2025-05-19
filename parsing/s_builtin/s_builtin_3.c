#include "../parsing.h"

int	p_find_env_var(char **envp, char *name)
{
	int		i;
	size_t	len;

	if (!envp || !name)
		return (-1);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && 
			(envp[i][len] == '=' || envp[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

char	*p_create_env_string(char *name, char *value)
{
	char	*result;
	char	*tmp;

	if (!name)
		return (NULL);
	if (!value)
		return (ft_strdup(name));
	tmp = ft_strjoin(name, "=");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, value);
	free(tmp);
	return (result);
}

char	**p_add_env_var(char **envp, char *new_var)
{
	char	**new_envp;
	int		count;
	int		i;

	if (!envp || !new_var)
		return (NULL);
	count = 0;
	while (envp[count])
		count++;
	new_envp = malloc(sizeof(char *) * (count + 2));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_envp[i] = envp[i];
		i++;
	}
	new_envp[count] = new_var;
	new_envp[count + 1] = NULL;
	free(envp);
	return (new_envp);
}

bool	p_remove_env_var(t_shell *lst, int index)
{
	char	**new_envp;
	int		count;
	int		i;
	int		j;

	if (!lst || !lst->envp || index < 0)
		return (false);
	count = 0;
	while (lst->envp[count])
		count++;
	new_envp = malloc(sizeof(char *) * count);
	if (!new_envp)
		return (false);
	i = 0;
	j = 0;
	while (lst->envp[i])
	{
		if (i != index)
			new_envp[j++] = lst->envp[i];
		else
			free(lst->envp[i]);
		i++;
	}
	new_envp[j] = NULL;
	free(lst->envp);
	lst->envp = new_envp;
	return (true);
}

bool	p_builtin_env(char **envp)
{
	int	i;

	if (!envp)
		return (false);
	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
			ft_putendl_fd(envp[i], STDOUT_FILENO);
		i++;
	}
	return (true);
}

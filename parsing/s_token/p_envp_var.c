#include "../parsing.h"

static char	*p_extract_env_name(char *var)
{
	char	*env_name;
	size_t	len;

	if (var[0] == '$')
		env_name = var + 1;
	else
		env_name = var;
	len = ft_strlen(env_name);
	if (len >= 2 && env_name[0] == '"' && env_name[len - 1] == '"')
		return (ft_substr(env_name, 1, len - 2));
	if (len >= 2 && env_name[0] == '\'' && env_name[len - 1] == '\'')
		return (NULL);
	return (ft_strdup(env_name));
}

static char	*p_find_env_value(char *env_name, char **envp)
{
	int		i;
	size_t	len;

	if (!env_name || !envp)
		return (NULL);
	len = ft_strlen(env_name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], env_name, len) == 0 && envp[i][len] == '=')
			return (ft_strdup(envp[i] + len + 1));
		i++;
	}
	return (ft_strdup(""));
}

void	p_envp_var(t_token *token, char **envp, char *env)
{
	char	*env_name;
	char	*value;

	if (!envp || !env)
		return ;
	env_name = p_extract_env_name(env);
	if (!env_name)
		return ;
	value = p_find_env_value(env_name, envp);
	free(env_name);
	if (value)
		token->value = value;
}

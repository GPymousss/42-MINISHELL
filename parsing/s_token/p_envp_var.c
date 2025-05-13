#include "../parsing.h"

void	p_envp_var(t_token *token, char **envp, char *env)
{
	size_t	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], env, ft_strlen(env)) == 0)
			token->value = ft_substr(envp[i], ft_strlen(env) + 1, ft_strlen(envp[i]) - 5);
		i++;
	}
}

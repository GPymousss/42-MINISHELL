#include "../parsing.h"

t_token	*p_init_token(char *value, t_quote type)
{
	t_token	*new;

	if (!value)
		return (NULL);
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	if (!new->value)
	{
		free(new);
		return (NULL);
	}
	new->type = type;
	new->next = NULL;
	return (new);
}

void	p_token_add_back(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!head || !new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	p_free_token_list(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		free(token->value);
		free(token);
		token = tmp;
	}
}

t_quote	p_check_quote_type(char *str)
{
	size_t	len;

	if (!str)
		return (NONE);
	len = ft_strlen(str);
	if (len >= 2 && str[0] == '\'' && str[len - 1] == '\'')
		return (SINGLE);
	if (len >= 2 && str[0] == '\"' && str[len - 1] == '\"')
		return (DOUBLE);
	return (NONE);
}

void	p_envp_var(t_token *token, char **envp, char *env)
{
	char	*env_name;
	char	*value;

	if (!token || !envp || !env)
		return ;
	if (ft_strcmp(env, "$?") == 0)
	{
		if (token->value)
			free(token->value);
		token->value = ft_strdup("0");
		return ;
	}
	env_name = p_extract_env_name(env);
	if (!env_name)
		return ;
	value = p_get_env_value(env_name, envp);
	free(env_name);
	if (value)
	{
		if (token->value)
			free(token->value);
		token->value = value;
	}
}

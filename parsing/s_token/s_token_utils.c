#include "../parsing.h"

char	*p_extract_env_name(char *var)
{
	char	*env_name;
	size_t	len;

	if (!var)
		return (NULL);
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

int	p_is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || 
			c == '\v' || c == '\f' || c == '\r');
}

int	p_is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	p_get_token_type(char *str)
{
	if (!str || !*str)
		return (-1);
	if (ft_strcmp(str, "|") == 0)
		return (1);
	if (ft_strcmp(str, "<") == 0)
		return (2);
	if (ft_strcmp(str, ">") == 0)
		return (3);
	if (ft_strcmp(str, "<<") == 0)
		return (4);
	if (ft_strcmp(str, ">>") == 0)
		return (5);
	return (0);
}

t_token	*p_tokenize(char *str, char **envp)
{
	t_token	*head;
	char	*start;
	t_quote	quote_state;
	int		i;

	if (!str)
		return (NULL);
	head = NULL;
	i = 0;
	while (str[i])
	{
		while (p_is_space(str[i]))
			i++;
		if (!str[i])
			break;
		start = &str[i];
		if (p_is_operator(str[i]))
			i = p_handle_operator(start, &i, &head);
		else
			i = p_handle_word(start, &i, &head, envp);
		if (i == -1)
			return (NULL);
	}
	return (head);
}

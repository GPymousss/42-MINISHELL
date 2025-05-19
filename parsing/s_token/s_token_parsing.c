#include "../parsing.h"

int	p_handle_operator(char *start, int *i, t_token **head)
{
	t_token	*new;
	char	*token_str;
	int		len;

	if (!start || !i || !head)
		return (-1);
	if (start[0] == '|')
		len = 1;
	else if (start[0] == '<' && start[1] == '<')
		len = 2;
	else if (start[0] == '>' && start[1] == '>')
		len = 2;
	else if (start[0] == '<' || start[0] == '>')
		len = 1;
	else
		return (-1);
	token_str = ft_substr(start, 0, len);
	if (!token_str)
		return (-1);
	new = p_init_token(token_str, NONE);
	free(token_str);
	if (!new)
		return (-1);
	p_token_add_back(head, new);
	return (*i + len);
}

int	p_skip_quotes(char *str, int *i, char quote)
{
	int	start;

	if (!str || !i)
		return (-1);
	start = *i;
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (!str[*i])
		return (-1);
	(*i)++;
	return (*i);
}

int	p_handle_word(char *start, int *i, t_token **head, char **envp)
{
	t_token	*new;
	char	*token_str;
	int		j;
	t_quote	type;

	if (!start || !i || !head)
		return (-1);
	j = *i;
	while (start[j - *i] && !p_is_space(start[j - *i]) 
		&& !p_is_operator(start[j - *i]))
	{
		if (start[j - *i] == '\'' || start[j - *i] == '\"')
		{
			if (p_skip_quotes(start, &j, start[j - *i]) == -1)
				return (-1);
		}
		else
			j++;
	}
	token_str = ft_substr(start, 0, j - *i);
	if (!token_str)
		return (-1);
	type = p_check_quote_type(token_str);
	new = p_init_token(token_str, type);
	free(token_str);
	if (!new)
		return (-1);
	if (new->value[0] == '$' && new->type != SINGLE)
		p_envp_var(new, envp, new->value);
	p_token_add_back(head, new);
	return (j);
}

int	p_count_tokens(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		count++;
		token = token->next;
	}
	return (count);
}

bool	p_token_to_cmd(t_token *token, t_shell *lst)
{
	t_token	*current;
	t_cmd	*cmd;
	int		type;

	if (!token || !lst)
		return (false);
	cmd = NULL;
	current = token;
	while (current)
	{
		type = p_get_token_type(current->value);
		if (type == 1)
		{
			if (!cmd)
				return (false);
			cmd = NULL;
		}
		else if (type >= 2 && type <= 5)
		{
			if (!p_handle_redirection(&current, lst, &cmd))
				return (false);
		}
		else
		{
			if (!p_handle_word_token(&current, lst, &cmd))
				return (false);
		}
		if (current)
			current = current->next;
	}
	return (true);
}

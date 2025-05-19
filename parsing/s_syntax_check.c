#include "parsing.h"

bool	p_check_syntax(t_token *token)
{
	if (!token)
		return (false);
	if (!p_is_valid_pipe(token))
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		return (false);
	}
	if (!p_is_valid_redir(token))
	{
		ft_putendl_fd("minishell: syntax error near unexpected token", 2);
		return (false);
	}
	return (true);
}

bool	p_is_valid_redir(t_token *token)
{
	int	type;

	while (token)
	{
		type = p_get_token_type(token->value);
		if (type >= 2 && type <= 5)
		{
			if (!token->next)
				return (false);
			if (p_get_token_type(token->next->value) != 0)
				return (false);
		}
		token = token->next;
	}
	return (true);
}

bool	p_is_valid_pipe(t_token *token)
{
	int	type;

	if (token && p_get_token_type(token->value) == 1)
		return (false);
	while (token)
	{
		type = p_get_token_type(token->value);
		if (type == 1)
		{
			if (!token->next)
				return (false);
			if (p_get_token_type(token->next->value) == 1)
				return (false);
		}
		token = token->next;
	}
	return (true);
}

bool	p_are_quotes_balanced(char *str)
{
	int		i;
	t_quote	state;

	if (!str)
		return (true);
	i = 0;
	state = NONE;
	while (str[i])
	{
		if (state == NONE)
		{
			if (str[i] == '\'')
				state = SINGLE;
			else if (str[i] == '\"')
				state = DOUBLE;
		}
		else if (state == SINGLE && str[i] == '\'')
			state = NONE;
		else if (state == DOUBLE && str[i] == '\"')
			state = NONE;
		i++;
	}
	return (state == NONE);
}

bool	p_is_valid_command(t_token *token)
{
	int	cmd_count;
	int	type;

	cmd_count = 0;
	while (token)
	{
		type = p_get_token_type(token->value);
		if (type == 0)
			cmd_count++;
		else if (type == 1)
		{
			if (cmd_count == 0)
				return (false);
			cmd_count = 0;
		}
		else if (type >= 2 && type <= 5)
		{
			token = token->next;
			if (!token)
				return (false);
		}
		if (token)
			token = token->next;
	}
	return (cmd_count > 0);
}

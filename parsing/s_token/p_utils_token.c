#include "../parsing.h"

t_token	*init_token(char *value, t_quote quote_type, t_token *next)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = value;
	new->quote_type = quote_type;
	new->next = next;
	return (new);
}

static int	add_token(t_token **tokens, char *start, int len, t_quote type)
{
	char	*value;

	value = ft_substr(start, 0, len);
	if (!value)
		return (0);
	token_add_back(tokens, init_token(value, type, NULL));
	return (1);
}

int	handle_default_token(char **input, char *start, t_token **tokens)
{
	while (**input && !is_metacharacter(**input))
		(*input)++;
	if (!add_token(tokens, start, *input - start, NONE))
		return (0);
	return (1);
}

void	token_clear(t_token **tokens)
{
	t_token	*tmp;

	if (!tokens || !*tokens)
		return ;
	while (*tokens)
	{
		tmp = (*tokens)->next;
		if ((*tokens)->value)
			free((*tokens)->value);
		free(*tokens);
		*tokens = tmp;
	}
	*tokens = NULL;
}

void	token_add_back(t_token **tokens, t_token *new)
{
	t_token *tmp;

	if (!tokens || !new)
		return ;
	if (!*tokens)
		*tokens = new;
	else
	{
		tmp = *tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
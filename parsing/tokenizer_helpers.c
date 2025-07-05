/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 00:00:00 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/06 00:00:00 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	add_token(t_token **tokens, char *value,
		t_token_type type, t_quote quote)
{
	t_token	*new;
	t_token	*cur;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->value = value;
	new->type = type;
	new->quote = quote;
	new->next = NULL;
	if (!*tokens)
		*tokens = new;
	else
	{
		cur = *tokens;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
}

static int	handle_double_operators(const char *line, int *i,
		char **op, t_token_type *type)
{
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		*op = ft_strdup("<<");
		*type = TOKEN_HERE_DOC;
		*i += 2;
		return (1);
	}
	else if (line[*i] == '>' && line[*i + 1] == '>')
	{
		*op = ft_strdup(">>");
		*type = TOKEN_APPEND;
		*i += 2;
		return (1);
	}
	return (0);
}

static int	handle_single_operators(const char *line, int *i,
		char **op, t_token_type *type)
{
	if (line[*i] == '<')
	{
		*op = ft_strdup("<");
		*type = TOKEN_REDIR_IN;
		(*i)++;
		return (1);
	}
	else if (line[*i] == '>')
	{
		*op = ft_strdup(">");
		*type = TOKEN_REDIR_OUT;
		(*i)++;
		return (1);
	}
	else if (line[*i] == '|')
	{
		*op = ft_strdup("|");
		*type = TOKEN_PIPE;
		(*i)++;
		return (1);
	}
	return (0);
}

int	handle_operator(const char *line, int *i, t_token **tokens)
{
	char			*op;
	t_token_type	type;

	op = NULL;
	if (handle_double_operators(line, i, &op, &type))
	{
		add_token(tokens, op, type, NONE);
		return (0);
	}
	if (handle_single_operators(line, i, &op, &type))
	{
		add_token(tokens, op, type, NONE);
		return (0);
	}
	return (-1);
}

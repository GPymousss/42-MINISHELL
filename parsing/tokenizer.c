/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:27:48 by llangana          #+#    #+#             */
/*   Updated: 2025/07/04 23:04:01 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	add_token(t_token **tokens, char *value, t_token_type type, t_quote quote)
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

static int	handle_operator(const char *line, int *i, t_token **tokens)
{
	char		*op;
	t_token_type	type;

	if (line[*i] == '<' && line[*i + 1] == '<')
		op = ft_strdup("<<"), type = TOKEN_HERE_DOC, *i += 2;
	else if (line[*i] == '>' && line[*i + 1] == '>')
		op = ft_strdup(">>"), type = TOKEN_APPEND, *i += 2;
	else if (line[*i] == '<')
		op = ft_strdup("<"), type = TOKEN_REDIR_IN, (*i)++;
	else if (line[*i] == '>')
		op = ft_strdup(">"), type = TOKEN_REDIR_OUT, (*i)++;
	else if (line[*i] == '|')
		op = ft_strdup("|"), type = TOKEN_PIPE, (*i)++;
	if (!op)
		return (-1);
	add_token(tokens, op, type, NONE);
	return (0);
}

static int	handle_word(const char *line, int *i, t_token **tokens)
{
	int		start;
	t_quote	quote;
	char	*word;
	t_quote	token_quote;

	start = *i;
	quote = NONE;
	token_quote = NONE;
	if (line[start] == '\'')
		token_quote = SINGLE;
	else if (line[start] == '"')
		token_quote = DOUBLE;
	while (line[*i] && (quote != NONE || (!is_whitespace(line[*i]) && !is_operator_start(line[*i]))))
	{
		quote = get_quote_state(line[*i], quote);
		(*i)++;
	}
	word = ft_substr(line, start, *i - start);
	if (!word)
		return (-1);
	add_token(tokens, word, TOKEN_WORD, token_quote);
	return (0);
}

int	tokenize(const char *line, t_token **tokens)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (is_whitespace(line[i]))
			i++;
		else if (is_operator_start(line[i]))
		{
			if (handle_operator(line, &i, tokens) == -1)
				return (-1);
		}
		else
		{
			if (handle_word(line, &i, tokens) == -1)
				return (-1);
		}
	}
	return (0);
}

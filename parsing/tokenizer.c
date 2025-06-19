/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:27:48 by llangana          #+#    #+#             */
/*   Updated: 2025/06/13 16:43:59 by llangana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	add_token(t_token **tokens, char *value, t_quote type)
{
	t_token	*new;
	t_token	*cur;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->value = value;
	new->type = type;
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
	char	*op;

	if (line[*i] == '<' && line[*i + 1] == '<')
		op = ft_strdup("<<");
	else if (line[*i] == '>' && line[*i + 1] == '>')
		op = ft_strdup(">>");
	else
		op = ft_substr(line, *i, 1);
	if (!op)
		return (-1);
	add_token(tokens, op, NONE);
	*i += ft_strlen(op);
	return (1);
}

static int	handle_word(const char *line, int *i, t_token **tokens)
{
	int		start;
	t_quote	quote;
	char	*word;
	t_quote	token_type;

	start = *i;
	quote = NONE;
	token_type = NONE;
	if (line[start] == '\'')
		token_type = SINGLE;
	else if (line[start] == '"')
		token_type = DOUBLE;
	while (line[*i] && (quote != NONE || !is_whitespace(line[*i])))
	{
		quote = get_quote_state(line[*i], quote);
		(*i)++;
	}
	word = ft_substr(line, start, *i - start);
	if (!word)
		return (-1);
	add_token(tokens, word, token_type);
	return (0);
}

int	tokenize(const char *line, t_token **tokens)
{
	int	i;
	int	res;

	i = 0;
	while (line[i])
	{
		if (is_whitespace(line[i]))
			i++;
		else if (is_operator_start(line[i]))
		{
			res = handle_operator(line, &i, tokens);
			if (res == -1)
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

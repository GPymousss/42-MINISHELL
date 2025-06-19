/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:27:59 by llangana          #+#    #+#             */
/*   Updated: 2025/06/13 14:28:00 by llangana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	is_operator_start(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

bool	is_redirection(const char *str)
{
	return (ft_strcmp(str, "<") == 0 || ft_strcmp(str, ">") == 0
		|| ft_strcmp(str, "<<") == 0 || ft_strcmp(str, ">>") == 0);
}

t_quote	get_quote_state(char c, t_quote current_quote)
{
	if (c == '\'' && current_quote != DOUBLE)
	{
		if (current_quote == SINGLE)
			return (NONE);
		return (SINGLE);
	}
	else if (c == '"' && current_quote != SINGLE)
	{
		if (current_quote == DOUBLE)
			return (NONE);
		return (DOUBLE);
	}
	return (current_quote);
}

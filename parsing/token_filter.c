/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_filter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 02:45:13 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/08 02:45:13 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	should_remove_token(t_token *token)
{
	if (token->type != TOKEN_WORD)
		return (0);
	if (!token->value)
		return (1);
	if (ft_strlen(token->value) == 0 && token->quote == NONE)
		return (1);
	return (0);
}

void	remove_empty_tokens(t_token **tokens)
{
	t_token	*prev;
	t_token	*current;
	t_token	*next;

	if (!tokens || !*tokens)
		return ;
	prev = NULL;
	current = *tokens;
	while (current)
	{
		next = current->next;
		if (should_remove_token(current))
		{
			if (prev)
				prev->next = next;
			else
				*tokens = next;
			free(current->value);
			free(current);
		}
		else
			prev = current;
		current = next;
	}
}

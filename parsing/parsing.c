/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:43:45 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/08 09:52:48 by llangana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	parsing(t_shell *shell)
{
	t_token	*tokens;

	tokens = NULL;
	if (tokenize(shell->input, &tokens) != 0)
	{
		free_tokens(tokens);
		return (false);
	}
	shell->tokens = tokens;
	expand_tokens(shell, tokens);
	remove_empty_tokens(&shell->tokens);
	if (!shell->tokens)
		return (true);
	if (parse_tokens_to_cmds(shell, shell->tokens) != 0)
	{
		free_cmds(shell->cmds);
		shell->cmds = NULL;
		return (false);
	}
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:43:45 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/04 23:03:43 by gletilly         ###   ########.fr       */
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
	if (parse_tokens_to_cmds(shell, tokens) != 0)
	{
		free_cmds(shell->cmds);
		shell->cmds = NULL;
		return (false);
	}
	return (true);
}

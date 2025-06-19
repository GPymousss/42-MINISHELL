/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:43:45 by gletilly          #+#    #+#             */
/*   Updated: 2025/06/13 14:28:14 by llangana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	parsing(t_shell *shell)
{
	t_token	*tokens;

	tokens = NULL;
	if (tokenize(shell->command, &tokens) != 0)
	{
		free_token_struct(tokens);
		return (false);
	}
	expand_tokens(shell, tokens);
	if (parse_tokens_to_cmds(shell, tokens) != 0)
	{
		free_token_struct(tokens);
		free_cmd_struct(shell->cmd);
		shell->cmd = NULL;
		return (false);
	}
	free_token_struct(tokens);
	return (true);
}

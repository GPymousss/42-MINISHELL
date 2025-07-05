/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:28:19 by llangana          #+#    #+#             */
/*   Updated: 2025/07/04 23:14:10 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	syntax_error(const char *msg)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (msg)
		ft_putstr_fd(msg, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
	return (-1);
}

static int	handle_redirection(t_cmd *cmd, t_token **cur)
{
	t_symbol	symbol;
	const char	*unexpected;
	t_token		*next;

	symbol = get_redir_symbol((*cur)->value);
	next = (*cur)->next;
	if (!next)
		return (syntax_error(NULL));
	if (next->type != TOKEN_WORD)
	{
		unexpected = next->value;
		return (syntax_error(unexpected));
	}
	add_redir_to_cmd(cmd, symbol, next->value);
	*cur = next->next;
	return (0);
}

static int	handle_pipe(t_cmd **cmd, t_token **cur)
{
	if (!(*cmd)->args)
		return (syntax_error((*cur)->value));
	(*cmd)->next = new_cmd();
	if (!(*cmd)->next)
		return (-1);
	*cmd = (*cmd)->next;
	*cur = (*cur)->next;
	return (0);
}

int	parse_tokens_to_cmds(t_shell *shell, t_token *tokens)
{
	t_token	*cur;
	t_cmd	*cmd;

	cmd = new_cmd();
	shell->cmds = cmd;
	cur = tokens;
	while (cur)
	{
		if (cur->type == TOKEN_PIPE)
		{
			if (handle_pipe(&cmd, &cur) != 0)
				return (-1);
		}
		else if (cur->type >= TOKEN_REDIR_IN && cur->type <= TOKEN_APPEND)
		{
			if (handle_redirection(cmd, &cur) != 0)
				return (-1);
		}
		else
		{
			add_arg_to_cmd(cmd, cur->value);
			cur = cur->next;
		}
	}
	return (0);
}

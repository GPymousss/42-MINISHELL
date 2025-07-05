/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:55:26 by lomont            #+#    #+#             */
/*   Updated: 2025/07/04 23:01:16 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	get_cmd_count(t_cmd *cmd)
{
	size_t	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

size_t	get_token_count(t_token *token)
{
	size_t	count;

	count = 0;
	while (token)
	{
		count++;
		token = token->next;
	}
	return (count);
}

size_t	get_redir_count(t_redir *redir)
{
	size_t	count;

	count = 0;
	while (redir)
	{
		count++;
		redir = redir->next;
	}
	return (count);
}

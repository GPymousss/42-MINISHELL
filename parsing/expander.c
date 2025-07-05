/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:28:36 by llangana          #+#    #+#             */
/*   Updated: 2025/07/04 23:02:33 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	copy_without_quotes(char *str, char *new)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '"' || str[i] == '\''))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		else
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
}

static void	process_expansion(t_shell *shell, t_token *token)
{
	char	*new_str;
	int		i;

	new_str = ft_strdup("");
	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '$' && token->quote != SINGLE)
		{
			i++;
			new_str = ft_strjoin_free(new_str,
					expand_variable(shell, token->value, &i));
		}
		else
			new_str = ft_strjoin_char(new_str, token->value[i++]);
	}
	free(token->value);
	token->value = new_str;
}

char	*remove_quotes(char *str)
{
	char	*new;
	int		len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	new = malloc(len + 1);
	if (!new)
		return (NULL);
	copy_without_quotes(str, new);
	free(str);
	return (new);
}

void	expand_tokens(t_shell *shell, t_token *tokens)
{
	t_token	*cur;

	cur = tokens;
	while (cur)
	{
		if (cur->quote == DOUBLE || cur->quote == NONE)
			process_expansion(shell, cur);
		cur->value = remove_quotes(cur->value);
		cur = cur->next;
	}
}

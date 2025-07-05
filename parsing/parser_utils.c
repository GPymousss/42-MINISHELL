/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:28:29 by llangana          #+#    #+#             */
/*   Updated: 2025/07/04 23:03:22 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_symbol	get_redir_symbol(const char *str)
{
	if (ft_strcmp(str, "<") == 0)
		return (REDIR_IN);
	if (ft_strcmp(str, ">") == 0)
		return (REDIR_OUT);
	if (ft_strcmp(str, "<<") == 0)
		return (HERE_DOC);
	if (ft_strcmp(str, ">>") == 0)
		return (APPEND);
	return (REDIR_OUT);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	free(s1);
	return (new);
}

char	*ft_strjoin_char(char *str, char c)
{
	char	*new;
	int		len;

	if (!str)
		len = 0;
	else
		len = ft_strlen(str);
	new = malloc(len + 2);
	if (!new)
		return (NULL);
	if (str)
		ft_memcpy(new, str, len);
	new[len] = c;
	new[len + 1] = '\0';
	free(str);
	return (new);
}

void	add_arg_to_cmd(t_cmd *cmd, char *arg)
{
	char	**new_args;
	int		count;
	int		i;

	count = 0;
	if (cmd->args)
		while (cmd->args[count])
			count++;
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return ;
	i = -1;
	while (++i < count)
		new_args[i] = cmd->args[i];
	new_args[count] = ft_strdup(arg);
	new_args[count + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
}

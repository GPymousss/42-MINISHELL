#include "../parsing.h"

char	*p_get_env_value(char *name, char **envp)
{
	int		i;
	size_t	len;

	if (!name || !envp)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (ft_strdup(envp[i] + len + 1));
		i++;
	}
	return (NULL);
}

void	p_print_tokens(t_token *head)
{
	t_token	*tmp;
	char	*type_str;

	tmp = head;
	printf("Token list:\n");
	while (tmp)
	{
		if (tmp->type == NONE)
			type_str = "NONE";
		else if (tmp->type == SINGLE)
			type_str = "SINGLE";
		else
			type_str = "DOUBLE";
		printf("  Value: [%s], Type: %s\n", tmp->value, type_str);
		tmp = tmp->next;
	}
}

void	p_print_commands(t_cmd *cmd)
{
	t_cmd	*tmp_cmd;
	t_redir	*tmp_redir;
	int		i;

	tmp_cmd = cmd;
	printf("Command list:\n");
	while (tmp_cmd)
	{
		printf("  Command: ");
		i = 0;
		while (tmp_cmd->cmd && tmp_cmd->cmd[i])
			printf("[%s] ", tmp_cmd->cmd[i++]);
		printf("\n");
		
		tmp_redir = tmp_cmd->redir;
		while (tmp_redir)
		{
			printf("    Redirection: %s %s\n", 
				p_get_redir_type_str(tmp_redir->symbol), 
				tmp_redir->str);
			tmp_redir = tmp_redir->next;
		}
		tmp_cmd = tmp_cmd->next;
	}
}

bool	p_remove_quotes(t_token *token)
{
	char	*new_value;
	size_t	len;

	if (!token || !token->value)
		return (false);
	if (token->type == NONE)
		return (true);
	len = ft_strlen(token->value);
	if (len < 2)
		return (true);
	new_value = ft_substr(token->value, 1, len - 2);
	if (!new_value)
		return (false);
	free(token->value);
	token->value = new_value;
	return (true);
}

bool	p_process_tokens(t_token *token, char **envp)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->value[0] == '$' && tmp->type != SINGLE)
			p_envp_var(tmp, envp, tmp->value);
		if (!p_remove_quotes(tmp))
			return (false);
		tmp = tmp->next;
	}
	return (true);
}

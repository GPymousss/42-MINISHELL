#include "../parsing.h"

t_cmd	*p_init_cmd(char **cmd_args)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = cmd_args;
	new->redir = NULL;
	new->next = NULL;
	return (new);
}

void	p_cmd_add_back(t_cmd **head, t_cmd *new)
{
	t_cmd	*tmp;

	if (!head || !new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

bool	p_add_redir_to_cmd(t_cmd *cmd, char *str, t_symbol symbol)
{
	t_redir	*new_redir;

	if (!cmd || !str)
		return (false);
	new_redir = p_init_redir(str, symbol);
	if (!new_redir)
		return (false);
	p_redir_add_back(&(cmd->redir), new_redir);
	return (true);
}

size_t	p_get_cmd_count(t_cmd *cmd)
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

bool	p_set_envp(t_shell *lst, char **envp)
{
	if (!lst || !envp)
		return (false);
	lst->envp = envp;
	return (true);
}

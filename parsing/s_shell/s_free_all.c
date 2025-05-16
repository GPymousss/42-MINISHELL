#include "../parsing.h"

static void	p_free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static void	p_free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		p_free_split(cmd->cmd);
		free(cmd);
		cmd = tmp;
	}
}

static void	p_free_redir_list(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->str);
		free(redir);
		redir = tmp;
	}
}

void	p_free_node_lst(t_shell *node)
{
	if (!node)
		return ;
	p_free_split(node->envp);
	p_free_cmd_list(node->cmd);
	p_free_redir_list(node->redir);
	free(node);
}

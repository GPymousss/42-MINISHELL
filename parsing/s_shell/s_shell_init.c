#include "../parsing.h"

t_shell	*p_init_lst(void)
{
	t_shell	*lst;

	lst = malloc(sizeof(t_shell));
	if (!lst)
		return (NULL);
	lst->envp = NULL;
	lst->cmd = NULL;
	lst->nb_pipe = 0;
	lst->fd_in = STDIN_FILENO;
	lst->fd_out = STDOUT_FILENO;
	lst->wstatus = 0;
	return (lst);
}

void	p_free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	p_free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		p_free_split(cmd->cmd);
		p_free_redir_list(cmd->redir);
		free(cmd);
		cmd = tmp;
	}
}

void	p_free_redir_list(t_redir *redir)
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
	p_free_cmd_list(node->cmd);
	if (node->fd_in != STDIN_FILENO)
		close(node->fd_in);
	if (node->fd_out != STDOUT_FILENO)
		close(node->fd_out);
	free(node);
}

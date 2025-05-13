#include "../parsing.h"

void	p_free_node_lst(t_shell *node)
{
	if (!node)
		return ;
	free(node->cmd);
	free(node->redir);
	free(node);
}

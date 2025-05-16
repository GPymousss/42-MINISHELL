#include "../parsing.h"

t_shell	*p_init_lst(void)
{
	t_shell	*lst;

	lst = malloc(sizeof(t_shell));
	if (!lst)
		return (NULL);
	lst->envp = NULL;
	lst->cmd = NULL;
	lst->redir = NULL;
	lst->nb_pipe = 0;
	lst->fd_in = STDIN_FILENO;
	lst->fd_out = STDOUT_FILENO;
	lst->hdc_idx = -1;
	lst->wstatus = 0;
	return (lst);
}

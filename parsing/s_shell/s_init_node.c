#include "../parsing.h"

t_shell	*p_init_lst(void)
{
	t_shell	*lst;

	lst = malloc(sizeof(t_shell));
	if (!lst)
		return (NULL);
	lst->cmd = NULL;
	lst->redir = NULL;
	lst->nb_pipe = 0;
	lst->wstatus = 0;
	lst->hdc_idx = -1;
	lst->next = NULL;
	return (lst);
}

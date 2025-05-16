#include "../parsing.h"

void	p_redir_add_back(t_redir **head, t_redir *new)
{
	t_redir	*tmp;

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

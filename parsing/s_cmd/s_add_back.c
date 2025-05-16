#include "../parsing.h"

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

#include "../parsing.h"

void	p_create_node_lst(t_shell **head)
{
	t_shell	*new;
	t_shell	*tmp;

	new = p_init_lst();
	if (!new)
		return (NULL);
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

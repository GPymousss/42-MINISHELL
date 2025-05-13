#include "../parsing.h"

void	p_free_all_lst(t_shell **head)
{
	t_shell	*tmp;
	t_shell	*next;

	if (!head || !*head)
		return ;
	tmp = *head;
	while (tmp)
	{
		next = tmp->next;
		p_free_node_lst(tmp);
		tmp = next;
	}
	*head = NULL;
}

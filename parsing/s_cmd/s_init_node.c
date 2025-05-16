#include "../parsing.h"

t_cmd	*p_init_cmd(char **cmd_args)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = cmd_args;
	new->next = NULL;
	return (new);
}

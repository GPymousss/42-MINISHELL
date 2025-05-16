#include "../parsing.h"

t_redir	*p_init_redir(char *str, t_symbol symbol)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->symbol = symbol;
	new->str = ft_strdup(str);
	if (!new->str)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

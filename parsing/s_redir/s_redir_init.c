#include "../parsing.h"

t_redir	*p_init_redir(char *str, t_symbol symbol)
{
	t_redir	*new;

	if (!str)
		return (NULL);
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

char	*p_get_redir_type_str(t_symbol symbol)
{
	if (symbol == REDIR_IN)
		return ("<");
	else if (symbol == REDIR_OUT)
		return (">");
	else if (symbol == HERE_DOC)
		return ("<<");
	else if (symbol == APPEND)
		return (">>");
	return ("unknown");
}

t_redir	*p_duplicate_redirection(t_redir *redir)
{
	t_redir	*new;

	if (!redir)
		return (NULL);
	new = p_init_redir(redir->str, redir->symbol);
	return (new);
}

bool	p_copy_redirections(t_redir *src, t_redir **dst)
{
	t_redir	*new;

	if (!dst)
		return (false);
	while (src)
	{
		new = p_duplicate_redirection(src);
		if (!new)
			return (false);
		p_redir_add_back(dst, new);
		src = src->next;
	}
	return (true);
}

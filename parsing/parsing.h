#ifndef PARSING_H
# define PARSING_H

# include "../minishell.h"

typedef struct s_token
{
	char			*value;
	struct s_token	*next;
}	t_token;

t_shell		*p_init_lst(void);
void		p_create_node_lst(t_shell **shell);
void		p_free_all_lst(t_shell **head);
void		p_free_node_lst(t_shell *node);

#endif

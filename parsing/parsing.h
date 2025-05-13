#ifndef PARSING_H
# define PARSING_H

# include "../minishell.h"

typedef enum s_quote
{
	NONE,
	SINGLE,
	DOUBLE,
}	t_quote;

typedef struct s_token
{
	char			*value;
	t_quote			quote_type;
	struct s_token	*next;
}	t_token;

t_shell		*p_init_lst(void);
void		p_create_node_lst(t_shell **shell);
void		p_free_all_lst(t_shell **head);
void		p_free_node_lst(t_shell *node);

bool		p_is_valid(int argc, char **argv, char **envp, t_shell *lst);

#endif

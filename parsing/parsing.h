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
	t_quote			type;
	struct s_token	*next;
}	t_token;

t_shell		*p_init_lst(void);
void		p_free_node_lst(t_shell *node);
void		p_free_split(char **arr);
void		p_free_cmd_list(t_cmd *cmd);
bool		p_set_envp(t_shell *lst, char **envp);

t_cmd		*p_init_cmd(char **cmd_args);
void		p_cmd_add_back(t_cmd **head, t_cmd *new);
bool		p_add_redir_to_cmd(t_cmd *cmd, char *str, t_symbol symbol);
size_t		p_get_cmd_count(t_cmd *cmd);

t_redir		*p_init_redir(char *str, t_symbol symbol);
void		p_redir_add_back(t_redir **head, t_redir *new);
void		p_free_redir_list(t_redir *redir);
char		*p_get_redir_type_str(t_symbol symbol);

t_token		*p_init_token(char *value, t_quote type);
void		p_token_add_back(t_token **head, t_token *new);
void		p_free_token_list(t_token *token);
t_quote		p_check_quote_type(char *str);
void		p_envp_var(t_token *token, char **envp, char *env);

char		*p_extract_env_name(char *var);
int			p_is_space(char c);
int			p_is_operator(char c);
int			p_get_token_type(char *str);
t_token		*p_tokenize(char *str, char **envp);

int			p_handle_operator(char *start, int *i, t_token **head);
int			p_skip_quotes(char *str, int *i, char quote);
int			p_handle_word(char *start, int *i, t_token **head, char **envp);
int			p_count_tokens(t_token *token);
bool		p_token_to_cmd(t_token *token, t_shell *lst);

bool		p_handle_redirection(t_token **token, t_shell *lst, t_cmd **cmd);
int			p_count_command_args(t_token *token);
char		**p_create_cmd_args(t_token *token, int count);
bool		p_handle_word_token(t_token **token, t_shell *lst, t_cmd **cmd);

char		*p_get_env_value(char *name, char **envp);
void		p_print_tokens(t_token *head);
void		p_print_commands(t_cmd *cmd);
bool		p_remove_quotes(t_token *token);
bool		p_process_tokens(t_token *token, char **envp);

bool		p_check_syntax(t_token *token);
bool		p_is_valid_redir(t_token *token);
bool		p_is_valid_pipe(t_token *token);
bool		p_are_quotes_balanced(char *str);
bool		p_is_valid_command(t_token *token);

bool		p_is_valid(char **envp, t_shell *lst);
bool		p_parse_line(char *line, t_shell *lst, char **envp);
bool		p_handle_heredoc(t_shell *lst);

#endif
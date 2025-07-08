/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 00:26:23 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/08 02:45:40 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include "../minishell.h"
# include "../exec/exec.h"

int			tokenize(const char *line, t_token **tokens);
void		add_token(t_token **tokens, char *value,
				t_token_type type, t_quote quote);
int			handle_operator(const char *line, int *i, t_token **tokens);
bool		is_whitespace(char c);
bool		is_operator_start(char c);
bool		is_redirection(const char *str);
t_quote		get_quote_state(char c, t_quote current_quote);
void		expand_tokens(t_shell *shell, t_token *tokens);
char		*expand_variable(t_shell *shell, const char *str, int *i);
char		*get_env_value(char **envp, const char *name);
int			parse_tokens_to_cmds(t_shell *shell, t_token *tokens);
t_cmd		*new_cmd(void);
void		add_arg_to_cmd(t_cmd *cmd, char *arg);
void		add_redir_to_cmd(t_cmd *cmd, t_symbol symbol, char *file);
t_symbol	get_redir_symbol(const char *str);
char		*ft_strjoin_char(char *str, char c);
char		*ft_strjoin_free(char *s1, char *s2);
char		*remove_quotes(char *str);
bool		parsing(t_shell *shell);
void		remove_empty_tokens(t_token **tokens);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 00:26:23 by gletilly          #+#    #+#             */
/*   Updated: 2025/06/13 14:44:14 by llangana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include "../minishell.h"
# include "../exec/exec.h"

// tokenizer.c
int			tokenize(const char *line, t_token **tokens);

// tokenizer_utils.c
bool		is_whitespace(char c);
bool		is_operator_start(char c);
bool		is_redirection(const char *str);
t_quote		get_quote_state(char c, t_quote current_quote);

// expander.c
void		expand_tokens(t_shell *shell, t_token *tokens);

// expander_utils.c
char		*expand_variable(t_shell *shell, const char *str, int *i);
char		*get_env_value(char **envp, const char *name);

// parser.c
int			parse_tokens_to_cmds(t_shell *shell, t_token *tokens);

//parser_utils.c
t_cmd		*new_cmd(void);
void		add_arg_to_cmd(t_cmd *cmd, char *arg);
t_symbol	get_redir_symbol(const char *str);
char		*ft_strjoin_char(char *str, char c);
char		*ft_strjoin_free(char *s1, char *s2);

// parsing.c
bool		parsing(t_shell *shell);

#endif

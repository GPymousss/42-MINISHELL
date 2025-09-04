/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <gletilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 07:13:07 by gletilly          #+#    #+#             */
/*   Updated: 2025/09/04 17:44:58 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum e_symbol
{
	REDIR_IN,
	REDIR_OUT,
	HERE_DOC,
	APPEND,
	PIPE,
}	t_symbol;

typedef enum e_quote
{
	NONE,
	SINGLE,
	DOUBLE,
}	t_quote;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HERE_DOC,
	TOKEN_APPEND,
}	t_token_type;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	t_quote				quote;
	struct s_token		*next;
}	t_token;

typedef struct s_redir
{
	t_symbol			symbol;
	char				*file;
	struct s_redir		*next;
}	t_redir;

typedef struct s_cmd
{
	char				**args;
	t_redir				*redir;
	struct s_cmd		*next;
}	t_cmd;

typedef struct s_envp
{
	char				*key;
	char				*value;
	struct s_envp		*next;
}	t_envp;

typedef struct s_pipe_data
{
	int		**pipes;
	int		cmd_index;
	int		cmd_count;
	pid_t	*pids;
}	t_pipe_data;

typedef struct s_shell
{
	char				*input;
	t_token				*tokens;
	t_cmd				*cmds;
	t_envp				*env;
	t_pipe_data			*pipe_data;
	char				**envp;
	int					exit_status;
	int					stdin_backup;
	int					stdout_backup;
}	t_shell;

#endif

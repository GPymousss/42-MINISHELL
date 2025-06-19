/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 07:13:07 by gletilly          #+#    #+#             */
/*   Updated: 2025/06/14 11:57:40 by llangana         ###   ########.fr       */
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
}	t_symbol;

typedef struct s_redir
{
	t_symbol		symbol;
	char			*str;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**cmd;
	t_redir			*redir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	char	*command;
	char	**envp;
	t_cmd	*cmd;
	size_t	nb_pipe;
	int		fd_in;
	int		fd_out;
	int		wstatus;
}	t_shell;

typedef enum e_quote
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

typedef struct s_pipe
{
	int	fdpipe[2];
	int	in_fd;
	int	fdpipe_index;
	int	pipe_index;
}	t_pipe;

typedef struct s_envp
{
	char			*envp;
	struct s_envp	*next;
}	t_envp;

#endif

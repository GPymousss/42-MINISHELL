/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 00:27:29 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/10 07:35:31 by llangana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <term.h>
# include <sys/ioctl.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdarg.h>
# include "struct.h"
# include "libft/libft.h"
# include "exec/exec.h"
# include "parsing/parsing.h"

extern volatile sig_atomic_t	g_heredoc_interrupted;

t_shell		*init_shell(char **envp);
void		sigint_handler(int sig);
void		sigquit_handler(int sig);
void		sigint_handler_ignore(int sig);
void		sigint_heredoc_handler(int sig);
void		setup_signals(void);
void		setup_signals_exec(void);
void		setup_child_signals(void);
void		setup_signals_heredoc(void);

#endif

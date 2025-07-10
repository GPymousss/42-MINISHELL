/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 00:27:29 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/10 06:36:52 by llangana         ###   ########.fr       */
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

t_shell			*init_shell(char **envp);

//signals.c
void			set_signals_interactive(void);
void			ignore_sigint(void);
void			set_signals_child(void);
void			set_signals_heredoc(void);
void			sigint_handler(int signal);
void			sigint_handler_heredoc(int signal);

#endif

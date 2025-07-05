/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 00:27:29 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/05 23:00:19 by gletilly         ###   ########.fr       */
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

t_shell	*init_shell(char **envp);

#endif
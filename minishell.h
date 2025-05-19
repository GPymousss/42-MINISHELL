#ifndef MINISHELL_H
# define MINISHELL_H

# include "exec/exec.h"
# include "parsing/parsing.h"
# include "libft/libft.h"

// readline, rl_clear_history, rl_on_new_line,
// rl_replace_line, rl_redisplay
# include <readline/readline.h>
// add_history
# include <readline/history.h>
// printf, perror
# include <stdio.h>
// malloc, free, exit, getenv
# include <stdlib.h>
// write, access, close, fork, getcwd, chdir,
// unlink, execve, dup, dup2, pipe, isatty, ttyslot
# include <unistd.h>
// open
# include <fcntl.h>
// wait, waitpid, wait3, wait4
# include <sys/wait.h>
// signal, sigaction, sigemptyset, sigaddset, kill
# include <signal.h>
// stat, lstat, fstat
# include <sys/stat.h>
// opendir, readdir, closedir
# include <dirent.h>
// strerror
# include <string.h>
// tcsetattr, tcgetattr
# include <termios.h>
// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <term.h>
// ioctl
# include <sys/ioctl.h>
// true / false
# include <stdbool.h>
// libft
# include <stddef.h>

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
	char	**envp;
	t_cmd	*cmd;
	size_t	nb_pipe;
	int		fd_in;
	int		fd_out;
	int		wstatus;
}	t_shell;

#endif

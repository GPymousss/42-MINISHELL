#ifndef MINISHELL_H
# define MINISHELL_H

# include "exec/exec.h"
# include "parsing/parsing.h"

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

#endif
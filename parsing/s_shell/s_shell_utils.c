#include "../parsing.h"

t_cmd	*p_add_cmd_to_shell(t_shell *lst, char **cmd_args)
{
	t_cmd	*new_cmd;

	if (!lst || !cmd_args)
		return (NULL);
	new_cmd = p_init_cmd(cmd_args);
	if (!new_cmd)
		return (NULL);
	p_cmd_add_back(&(lst->cmd), new_cmd);
	lst->nb_pipe = p_get_cmd_count(lst->cmd) - 1;
	return (new_cmd);
}

bool	p_setup_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (false);
	}
	return (true);
}

bool	p_redirect_io(int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			return (false);
		close(fd_in);
	}
	if (fd_out != STDOUT_FILENO)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			return (false);
		close(fd_out);
	}
	return (true);
}

int	p_get_exit_status(t_shell *lst)
{
	if (!lst)
		return (127);
	if (WIFEXITED(lst->wstatus))
		return (WEXITSTATUS(lst->wstatus));
	else if (WIFSIGNALED(lst->wstatus))
		return (128 + WTERMSIG(lst->wstatus));
	return (lst->wstatus);
}

void	p_wait_for_children(pid_t *pid, int count, int *wstatus)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (waitpid(pid[i], wstatus, 0) == -1)
			perror("waitpid");
		i++;
	}
}

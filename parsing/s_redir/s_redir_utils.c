#include "../parsing.h"

bool	p_handle_redir_out(t_redir *redir, int *fd_out)
{
	if (*fd_out != STDOUT_FILENO)
		close(*fd_out);
	*fd_out = open(redir->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd_out == -1)
	{
		perror(redir->str);
		return (false);
	}
	return (true);
}

bool	p_handle_redir_append(t_redir *redir, int *fd_out)
{
	if (*fd_out != STDOUT_FILENO)
		close(*fd_out);
	*fd_out = open(redir->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd_out == -1)
	{
		perror(redir->str);
		return (false);
	}
	return (true);
}

bool	p_handle_here_doc(t_redir *redir, int *fd_in)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (false);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, redir->str) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, pipefd[1]);
		free(line);
	}
	close(pipefd[1]);
	if (*fd_in != STDIN_FILENO)
		close(*fd_in);
	*fd_in = pipefd[0];
	return (true);
}

bool	p_process_redirections(t_redir *redir, int *fd_in, int *fd_out)
{
	while (redir)
	{
		if (redir->symbol == REDIR_IN)
		{
			if (!p_handle_redir_in(redir, fd_in))
				return (false);
		}
		else if (redir->symbol == REDIR_OUT)
		{
			if (!p_handle_redir_out(redir, fd_out))
				return (false);
		}
		else if (redir->symbol == APPEND)
		{
			if (!p_handle_redir_append(redir, fd_out))
				return (false);
		}
		else if (redir->symbol == HERE_DOC)
		{
			if (!p_handle_here_doc(redir, fd_in))
				return (false);
		}
		redir = redir->next;
	}
	return (true);
}

int	p_count_redir_by_type(t_redir *redir, t_symbol symbol)
{
	int	count;

	count = 0;
	while (redir)
	{
		if (redir->symbol == symbol)
			count++;
		redir = redir->next;
	}
	return (count);
}

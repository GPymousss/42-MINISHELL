#include "parsing.h"

bool	p_parse_line(char *line, t_shell *lst, char **envp)
{
	t_token	*tokens;
	bool	result;

	if (!line || !lst || !envp)
		return (false);
	if (!*line)
		return (true);
	if (!p_are_quotes_balanced(line))
	{
		ft_putendl_fd("minishell: syntax error: unbalanced quotes", 2);
		return (false);
	}
	tokens = p_tokenize(line, envp);
	if (!tokens)
		return (false);
	if (!p_check_syntax(tokens))
	{
		p_free_token_list(tokens);
		return (false);
	}
	if (!p_process_tokens(tokens, envp))
	{
		p_free_token_list(tokens);
		return (false);
	}
	result = p_token_to_cmd(tokens, lst);
	p_free_token_list(tokens);
	if (!result)
		return (false);
	lst->nb_pipe = p_get_cmd_count(lst->cmd) - 1;
	if (!p_handle_heredoc(lst))
		return (false);
	return (true);
}

bool	p_handle_heredoc(t_shell *lst)
{
	t_cmd	*cmd;
	t_redir	*redir;
	int		pipefd[2];
	char	*line;

	if (!lst)
		return (false);
	cmd = lst->cmd;
	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->symbol == HERE_DOC)
			{
				if (pipe(pipefd) == -1)
					return (false);
				while (1)
				{
					line = readline("> ");
					if (!line || ft_strcmp(line, redir->str) == 0)
					{
						free(line);
						break;
					}
					ft_putendl_fd(line, pipefd[1]);
					free(line);
				}
				close(pipefd[1]);
				redir->symbol = REDIR_IN;
				free(redir->str);
				redir->str = ft_itoa(pipefd[0]);
				if (!redir->str)
					return (false);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (true);
}

bool	p_is_valid(char **envp, t_shell *lst)
{
	char	*line;
	bool	result;

	if (!envp || !lst)
		return (false);
	line = readline("bash-5.1$ ");
	if (!line)
		return (false);
	if (*line)
		add_history(line);
	result = p_parse_line(line, lst, envp);
	free(line);
	return (result);
}

int	p_find_heredocs(t_cmd *cmd)
{
	t_redir	*redir;
	int		count;

	if (!cmd)
		return (0);
	count = 0;
	redir = cmd->redir;
	while (redir)
	{
		if (redir->symbol == HERE_DOC)
			count++;
		redir = redir->next;
	}
	return (count);
}

char	*p_expand_variables(char *str, char **envp)
{
	char	*result;
	char	*var_name;
	char	*var_value;
	int		i;
	int		j;

	if (!str || !envp)
		return (NULL);
	if (!ft_strchr(str, '$'))
		return (ft_strdup(str));
	result = ft_strdup(str);
	return (result);
}

#include "../parsing.h"

bool	p_is_numeric(char *str)
{
	int	i;

	if (!str || !*str)
		return (false);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

long	p_atol(char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

bool	p_is_valid_exit_arg(char *arg)
{
	long	value;

	if (!p_is_numeric(arg))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": numeric argument required", 2);
		return (false);
	}
	value = p_atol(arg);
	return (true);
}

bool	p_builtin_exit(char **args, t_shell *lst)
{
	int	exit_status;

	if (!args || !args[0] || !lst)
		return (false);
	ft_putendl_fd("exit", 2);
	if (!args[1])
		exit(p_get_exit_status(lst));
	if (!p_is_valid_exit_arg(args[1]))
		exit(255);
	if (args[2])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (false);
	}
	exit_status = (unsigned char)p_atol(args[1]);
	exit(exit_status);
	return (true);
}

bool	p_execute_pipeline(t_shell *lst)
{
	pid_t	*pid;
	int		pipefd[2];
	int		prev_pipe;
	t_cmd	*cmd;
	int		i;

	if (!lst || !lst->cmd)
		return (false);
	pid = malloc(sizeof(pid_t) * (lst->nb_pipe + 1));
	if (!pid)
		return (false);
	i = 0;
	cmd = lst->cmd;
	prev_pipe = STDIN_FILENO;
	while (i <= lst->nb_pipe)
	{
		if (i < lst->nb_pipe && !p_setup_pipe(pipefd))
			return (false);
		pid[i] = fork();
		if (pid[i] == -1)
			return (false);
		if (pid[i] == 0)
			p_execute_child(cmd, lst, prev_pipe, i < lst->nb_pipe ? pipefd[1] : STDOUT_FILENO);
		p_parent_process(prev_pipe, pipefd, i < lst->nb_pipe);
		cmd = cmd->next;
		i++;
	}
	p_wait_for_children(pid, lst->nb_pipe + 1, &lst->wstatus);
	free(pid);
	return (true);
}

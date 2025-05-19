#include "minishell.h"

static void	debug_print_shell(t_shell *lst)
{
	printf("Shell structure:\n");
	printf("  Number of pipes: %zu\n", lst->nb_pipe);
	p_print_commands(lst->cmd);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*lst;
	bool	success;

	(void)argc;
	(void)argv;
	while (1)
	{
		lst = p_init_lst();
		if (!lst)
			exit(EXIT_FAILURE);
		p_set_envp(lst, envp);
		success = p_is_valid(envp, lst);
		if (success)
			debug_print_shell(lst);
		p_free_node_lst(lst);
	}
	return (0);
}

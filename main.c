#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	*lst;

	if (!p_is_valid(argc, argv, envp, &lst))
		return (0);
	printf("Ok\n");
	return (0);
}
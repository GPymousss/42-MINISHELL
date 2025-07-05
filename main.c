/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 00:31:50 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/05 04:39:39 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_full_parsing(t_shell *shell, char *input);

static void	handle_command(t_shell *shell, char *input)
{
	shell->input = input;
	if (!input || ft_strlen(input) == 0)
	{
		free(input);
		return ;
	}
	if (ft_strncmp(input, "DEBUG ", 6) == 0)
		debug_full_parsing(shell, input + 6);
	else if (parsing(shell))
		exec(shell);
	if (ft_strncmp(input, "", 1) != 0)
		add_history(input);
	free(input);
	shell->input = NULL;
	if (shell->tokens)
	{
		free_tokens(shell->tokens);
		shell->tokens = NULL;
	}
	if (shell->cmds)
	{
		free_cmds(shell->cmds);
		shell->cmds = NULL;
	}
}

static void	handle_eof(t_shell *shell)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	free_shell(shell);
	exit(shell->exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	if (!shell)
		return (EXIT_FAILURE);
	while (1)
	{
		input = readline("bash-5.1$ ");
		if (input == NULL)
			handle_eof(shell);
		handle_command(shell, input);
	}
	return (EXIT_SUCCESS);
}

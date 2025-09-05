/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 00:31:50 by gletilly          #+#    #+#             */
/*   Updated: 2025/09/04 23:29:31 by llangana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_command(t_shell *shell, char *input)
{
	shell->input = input;
	if (!input || ft_strlen(input) == 0)
	{
		free(input);
		return ;
	}
	if (parsing(shell))
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
	int	exit_code;

	ft_putendl_fd("exit", STDOUT_FILENO);
	exit_code = shell->exit_status;
	if (shell->stdin_backup != -1)
		close(shell->stdin_backup);
	if (shell->stdout_backup != -1)
		close(shell->stdout_backup);
	free_shell(shell);
	exit(exit_code);
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
	setup_signals();
	while (1)
	{
		input = readline("bash-5.1$ ");
		if (g_heredoc_interrupted)
		{
			shell->exit_status = 130;
			g_heredoc_interrupted = 0;
		}
		if (input == NULL)
		{
			shell->input = NULL;
			handle_eof(shell);
		}
		handle_command(shell, input);
	}
	return (EXIT_SUCCESS);
}

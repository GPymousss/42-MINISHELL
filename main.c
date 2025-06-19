/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 00:31:50 by gletilly          #+#    #+#             */
/*   Updated: 2025/06/15 10:37:53 by llangana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_command(t_shell *shell, char *command)
{
	shell->command = command;
	if (parsing(shell))
		exec(shell);
	if (ft_strncmp(command, "", 1) != 0)
		add_history(command);
	free(command);
	shell->command = NULL;
	if (shell->cmd)
	{
		free_cmd_struct(shell->cmd);
		shell->cmd = NULL;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*command;
	t_shell	*shell;

	shell = init_shell();
	shell->envp = envp;
	while (1)
	{
		command = readline("bash-5.1$ ");
		if (command == NULL)
		{
			free_shell(shell);
			free(shell);
			exit(EXIT_SUCCESS);
		}
		handle_command(shell, command);
	}
	(void)argc;
	(void)argv;
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:18:29 by llangana          #+#    #+#             */
/*   Updated: 2025/07/10 05:20:44 by llangana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t	g_sig = 0;

void	set_signals_heredoc(void)
{
	struct sigaction	sa_sigint;

	ft_bzero(&sa_sigint, sizeof(sa_sigint));
	sa_sigint.sa_handler = &sigint_handler_heredoc;
	sa_sigint.sa_flags = 0;
	sigaction(SIGINT, &sa_sigint, NULL);
}

void	set_signals_child(void)
{
	struct sigaction	sa_child;
	struct sigaction	sa_child_quit;

	ft_bzero(&sa_child, sizeof(sa_child));
	sa_child.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa_child, NULL);
	ft_bzero(&sa_child_quit, sizeof(sa_child_quit));
	sa_child_quit.sa_handler = SIG_IGN;
	sa_child_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_child_quit, NULL);
}

void	set_signals_interactive(void)
{
	struct sigaction	sa;
	struct sigaction	sb;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = &sigint_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	ft_bzero(&sb, sizeof(sb));
	sb.sa_handler = SIG_IGN;
	sb.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sb, NULL);
}

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_sig = signal;
	}
}

void	sigint_handler_heredoc(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n", 2);
	g_sig = 2;
}

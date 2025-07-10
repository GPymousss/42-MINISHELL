/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 05:11:10 by llangana          #+#    #+#             */
/*   Updated: 2025/07/10 05:20:26 by llangana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ignore_sigint(void)
{
	struct sigaction	sa_ignore;
	struct sigaction	sa_child_quit;

	ft_bzero(&sa_ignore, sizeof(sa_ignore));
	sa_ignore.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_ignore, NULL);
	ft_bzero(&sa_child_quit, sizeof(sa_child_quit));
	sa_child_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_child_quit, NULL);
}

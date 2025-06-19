/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 06:52:22 by gletilly          #+#    #+#             */
/*   Updated: 2025/06/15 10:58:58 by llangana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"

char	*join_args(char *arg, char *new_arg)
{
	char	*tmp;

	if (!new_arg)
		new_arg = ft_strdup("");
	if (!new_arg)
		return (NULL);
	tmp = new_arg;
	new_arg = ft_strjoin(new_arg, arg);
	free(tmp);
	tmp = new_arg;
	new_arg = ft_strjoin(new_arg, "/");
	free(tmp);
	free(arg);
	return (new_arg);
}

char	*check_arg(char *arg, char **envp)
{
	if (ft_strncmp(arg, ".", 2) == 0)
		arg = get_specific_env(envp, "PWD=");
	else if (ft_strncmp(arg, "..", 3) == 0)
		arg = get_prev_pwd(envp);
	else if (ft_strncmp(arg, "~", 2) == 0)
		arg = get_specific_env(envp, "HOME=");
	else if (ft_strncmp(arg, "-", 2) == 0)
		arg = get_specific_env(envp, "OLDPWD=");
	return (arg);
}

int	check_arg_nbr(t_shell *shell)
{
	size_t	i;

	i = 0;
	while (shell->cmd->cmd[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("bash: cd: too many arguments", 2);
		return (-1);
	}
	return (0);
}

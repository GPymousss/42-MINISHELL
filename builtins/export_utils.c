/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 06:57:20 by gletilly          #+#    #+#             */
/*   Updated: 2025/06/15 10:49:00 by llangana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"

char	*remove_extra_char_before_egal(char *arg)
{
	size_t	i;
	char	*new_arg;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (i > 0 && arg[i] == '=' && arg[i - 1] == '+')
	{
		new_arg = malloc(ft_strlen(arg));
		if (!new_arg)
			return (NULL);
		ft_strlcpy(new_arg, arg, i);
		ft_strlcat(new_arg, arg + i, ft_strlen(arg));
		return (new_arg);
	}
	return (ft_strdup(arg));
}

bool	check_arg_export_syntax(char *arg)
{
	size_t	i;

	i = 0;
	if (arg[0] == '-' && arg[1] != '\0')
	{
		ft_putstr_fd("export: ", STDERR_FILENO);
		ft_putchar_fd(arg[0], STDERR_FILENO);
		ft_putchar_fd(arg[1], STDERR_FILENO);
		ft_putstr_fd(": invalid option\n", STDERR_FILENO);
		ft_putstr_fd("export: usage: export [name[=value] ...]\n",
			STDERR_FILENO);
		return (false);
	}
	if (arg[0] != '_' && !ft_isalpha(arg[0]))
		return (error_export(arg));
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] != '_' && !ft_isalnum(arg[i])
			&& !(arg[i] == '+' && arg[i + 1] == '='))
			return (error_export(arg));
		i++;
	}
	return (true);
}

bool	error_export(char *arg)
{
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	return (false);
}

char	*remove_char_arg(char *arg)
{
	char	*new_arg;
	size_t	i;

	i = 0;
	new_arg = malloc(sizeof(char) * (ft_strlen(arg)));
	if (!new_arg)
		return (NULL);
	while (arg[i] != '=')
		i++;
	ft_memmove(new_arg, arg, i - 1);
	ft_memmove(new_arg + i - 1, arg + i, ft_strlen(arg) - i);
	new_arg[ft_strlen(arg) - 1] = '\0';
	return (new_arg);
}

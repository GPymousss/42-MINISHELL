/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 00:27:59 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/05 04:46:03 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../minishell.h"
# include "../parsing/parsing.h"
# include "../libft/libft.h"

# define CMD_NOT_FOUND 127
# define PERMISSION_DENIED 126

int		exec(t_shell *shell);
int		execute_single_cmd(t_shell *shell, t_cmd *cmd);
int		execute_external_cmd(t_shell *shell, t_cmd *cmd);
char	*find_command_path(char *cmd, char **envp);
void	handle_exec_error(char *cmd, int error_code);
char	*get_path_env(char **envp);
char	**split_path(char *path_env);
int		is_valid_command(char *path);

#endif
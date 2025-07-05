/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 22:17:47 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/05 22:17:47 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"
# include "../libft/libft.h"

int		is_builtin(char *cmd);
int		execute_builtin(t_shell *shell, t_cmd *cmd);
int		builtin_pwd(t_shell *shell, t_cmd *cmd);
int		builtin_cd(t_shell *shell, t_cmd *cmd);
int		builtin_echo(t_shell *shell, t_cmd *cmd);
int		builtin_env(t_shell *shell, t_cmd *cmd);
int		builtin_export(t_shell *shell, t_cmd *cmd);
int		builtin_unset(t_shell *shell, t_cmd *cmd);
int		builtin_exit(t_shell *shell, t_cmd *cmd);

t_envp	*find_env_node(t_envp *env, char *key);
void	update_env_node(t_envp *node, char *new_value);
t_envp	*create_env_node(char *key, char *value);
void	add_env_node(t_shell *shell, char *key, char *value);
void	rebuild_envp_array(t_shell *shell);

#endif
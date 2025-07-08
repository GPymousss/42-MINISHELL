/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 00:27:59 by gletilly          #+#    #+#             */
/*   Updated: 2025/07/08 02:55:46 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../minishell.h"
# include "../parsing/parsing.h"
# include "../libft/libft.h"

# define CMD_NOT_FOUND 127
# define PERMISSION_DENIED 126

typedef struct s_pipe_data
{
	int		**pipes;
	int		cmd_index;
	int		cmd_count;
}	t_pipe_data;

int		exec(t_shell *shell);
int		execute_single_cmd(t_shell *shell, t_cmd *cmd);
int		execute_external_cmd(t_shell *shell, t_cmd *cmd);
char	*find_command_path(char *cmd, char **envp);
char	*find_command_path_with_error(char *cmd, char **envp,
			int *error_code, int *is_dir);
void	handle_exec_error(char *cmd, int error_code);
char	*get_path_env(char **envp);
char	**split_path(char *path_env);
int		is_valid_command(char *path);
int		execute_pipeline(t_shell *shell, t_cmd *cmds);
void	execute_pipe_child(t_shell *shell, t_cmd *cmd, t_pipe_data *data);
int		wait_for_pipeline(pid_t *pids, int **pipes, int cmd_count);
int		apply_redirections(t_cmd *cmd);
int		apply_single_redirection(t_redir *redir);
int		handle_heredoc_redirection(char *delimiter);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 00:27:59 by gletilly          #+#    #+#             */
/*   Updated: 2025/09/04 15:14:08 by llangana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../minishell.h"
# include "../parsing/parsing.h"
# include "../libft/libft.h"

# define CMD_NOT_FOUND 127
# define PERMISSION_DENIED 126

/*
typedef struct s_pipe_data
{
	int		**pipes;
	int		cmd_index;
	int		cmd_count;
}	t_pipe_data;
*/

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
int		apply_redirections(t_shell *shell, t_cmd *cmd);
int		apply_single_redirection(t_shell *shell, t_redir *redir);
int		handle_heredoc_redirection(t_shell *shell, char *delimiter);
void	setup_child_signals(void);
void	setup_signals_exec(void);
void	setup_signals(void);
void	setup_signals_heredoc(void);
void	close_all_pipes(int **pipes, int cmd_count);
int		heredoc_failed(int status);
void	close_backup_in_child(t_shell *shell);

#endif

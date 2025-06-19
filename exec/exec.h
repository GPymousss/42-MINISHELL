/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gletilly <pymousss.dev@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 00:27:59 by gletilly          #+#    #+#             */
/*   Updated: 2025/06/19 09:34:38 by gletilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../minishell.h"
# include "../parsing/parsing.h"
# include "../libft/libft.h"

// exec_cmd.c

int			exec_cmd(t_shell *shell);
pid_t		*fork_cmd(t_shell *shell, t_pipe *pipex);
void		create_children(t_shell *shell, pid_t *id_fork, t_pipe *pipex);
void		create_child(t_shell *shell, t_pipe *pipex);

// exec_utils.c

void		redir_cmd_input_output(t_shell *shell);
void		ft_dup(t_shell *shell, t_pipe *pipex, char *command_path);
int			dup_pipe(t_shell *shell, t_pipe *pipex);
void		ft_dup_redir(t_shell *shell);

// exec.c

void		exec(t_shell *shell);
bool		exec_built_in_inside_child(t_shell *shell);
int			exec_built_in(t_shell *shell);
bool		is_cmd_built_ins(t_shell *shell);

// here_doc.c

char		*here_doc(t_shell *shell, int i);
void		read_heredoc(t_shell *shell, int fd);
int			ft_tmp_open_heredoc(char *name, int i);
bool		ft_is_last_fd_in(t_shell *shell);

// infile.c

void		redir_infile(t_shell *shell);

// outfile.c

void		redir_outfile(t_shell *shell);

// pipex_utils.c

t_pipe		*init_struct_pipex(void);
void		pipe_struct_update(t_shell *shell, t_pipe *pipex, size_t i);

// utils_exec.c

t_pipe		*set_struct_pipex(t_shell *shell);
char		*find_command_exist_executable(t_shell *shell, t_pipe *pipex);
int			ft_wait(t_shell *shell, pid_t *id_fork, size_t nb_pipes);

// utils_path.c

char		*check_command_path(char *command, char **envp);
char		*recup_env(char **envp);
char		*new_command_function(char **path, char *new_command);

# define FIRST_PIPE 1
# define N_PIPE 2
# define LAST_PIPE 3

// cd.c

int			exec_cd(char *arg);
int			ft_cd(t_shell *shell);
void		find_change_env(t_envp *env, char *new_env, char *env_to_replace);
char		**ft_convert_node_to_envp(t_envp *env);
void		update_pwd(t_shell *shell, char *arg);
char		*join_args(char *arg, char *new_arg);
char		*check_arg(char *arg, char **envp);
char		*get_cd_argument(char *cmd, char **envp);
int			check_arg_nbr(t_shell *shell);
char		*get_specific_env(char **envp, char *env);
char		*get_prev_pwd(char **envp);

// echo.c

void		echo_w_arg(t_shell *shell);
int			ft_echo(t_shell *shell);

// env.c

int			ft_env(t_shell *shell);

// exit.c

void		ft_exit(t_shell *shell);

// export.c

int			ft_export(t_shell *shell);
void		export_arg_to_env(t_shell *shell, char *arg);
char		*remove_char_arg(char *arg);
char		*remove_extra_char_before_egal(char *arg);
bool		check_arg_export_syntax(char *arg);
bool		error_export(char *arg);
void		export_all(char **envp);

// pwd.c

int			ft_pwd(bool print);

// unset.c

t_envp		*ft_delone_env(t_envp *lst, char *env_to_find);
bool		check_if_in_envp(char **envp, char *str);
int			ft_unset(t_shell *shell);

// unset_utils.c
void		ft_unset_var(t_shell *shell, char *name_to_unset);

// utils_env.c

t_envp		*ft_last_envp(t_envp *lst);
void		ft_add_back_envp(t_envp **lst, t_envp *new);
char		**ft_malloc_envp(char **envp);
t_envp		*create_node_envp(char *env);
t_envp		*fill_envp(t_envp *node, char **envp);

#endif

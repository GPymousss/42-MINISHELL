/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llangana <llangana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 00:22:56 by gletilly          #+#    #+#             */
/*   Updated: 2025/08/04 23:11:34 by llangana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "../minishell.h"
# include "../parsing/parsing.h"
# include "../exec/exec.h"

// IS FUNCTIONS
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isprint(int c);
int			ft_isascii(int c);
int			ft_isspace(int c);
int			ft_isnegative(long c);

// MEM FUNCTIONS
void		ft_bzero(void *s, size_t n);
void		*ft_memset(void *s, int c, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);

// PUT FUNCTIONS
void		ft_putnbr_fd(int n, int fd);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(const char *s, int fd);
void		ft_putendl_fd(char *s, int fd);

// CONVERT FUNCTIONS
char		*ft_itoa(int n);
int			ft_tolower(int c);
int			ft_toupper(int c);
int			ft_atoi(const char *str);
long		ft_atol(const char *str);

// STR FUNCTIONS
size_t		ft_strlen(const char *string);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
char		*ft_strdup(const char *s);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		**ft_split(const char *s, char c);
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_strtrim(const char *s1, const char *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char		*ft_strnstr(const char *big, const char *little, size_t len);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);

// ADD BACK FUNCTIONS
void		token_add_back(t_token **head, t_token *new);
void		redir_add_back(t_redir **head, t_redir *new);
void		cmd_add_back(t_cmd **head, t_cmd *new);
void		envp_add_back(t_envp **head, t_envp *new);

// INIT FUNCTIONS
t_shell		*init_shell(char **envp);
t_token		*init_token(char *value, t_token_type type, t_quote quote);
t_redir		*init_redir(char *file, t_symbol symbol);
t_cmd		*init_cmd(void);
t_envp		*init_envp(char *key, char *value);

// SHELL FUNCTIONS
size_t		get_cmd_count(t_cmd *cmd);
size_t		get_token_count(t_token *token);
size_t		get_redir_count(t_redir *redir);
char		*get_env_value_from_envp(char *name, char **envp);
char		*get_env_value_from_list(char *name, t_envp *env);

// FREE FUNCTIONS
void		free_all(t_shell *shell);
void		free_array(char **array);
void		free_cmds(t_cmd *cmd);
void		free_redirs(t_redir *redir);
void		free_tokens(t_token *token);
//void		free_envp_struct(t_envp *env);
void		free_env(t_envp *env);
void		free_envp(char **envp);
void		free_shell(t_shell *shell);
char		*ft_strjoin_free(char *s1, char *s2);
char		**free_array_partial(char **arr, int count);
void		free_pipe_data(t_pipe_data *data);

// PRINTF
void		print_array(char **array);
int			ft_print_nbr(int n);
int			ft_print_str(char *s);
int			ft_print_char(char c);
int			ft_print_hexaptr(void *n);
int			ft_put_unsigned(unsigned int n);
int			ft_puthexa_upper(unsigned int n);
int			ft_puthexa_lower(unsigned int n);
int			ft_printf(const char *string, ...);
int			ft_puthexa_ptr(unsigned long address);

// GET_NEXT_LINE
# define BUFFER_SIZE 42

char		*get_next_line(int fd);

#endif

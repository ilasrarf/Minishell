/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:59:09 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/05/25 16:43:36 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// int						i;

typedef struct s_lexeing
{
	char				*word;
	char				type;
	int					in_quotes;
	struct s_lexeing	*next;
}						t_lexer;

typedef struct s_norm
{
	int					i;
	int					in;
	int					out;
}						t_norm;

typedef struct s_parser
{
	char				**args;
	int					in_red;
	int					out_red;
	struct s_parser		*next;
}						t_parser;

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_calcul
{
	int					i;
	int					j;
	int					k;
	int					len;
}						t_calcul;

typedef struct s_var
{
	int					exit_s;
	int					i;
	int					*shell_lvl;
	char				*name;
	char				*path;
	char				*value;
	struct s_var		*next;
}						t_var;

extern t_var			*g_var;

// lexer functions
int						ft_check_quotes(char *str);
void					ft_lexer(char *str, t_lexer **lex);
void					ft_handel_char(t_lexer **lex, char **str);
void					ft_handel_var(t_lexer **lex, char **str);
void					ft_handel_herdoc_fm(t_lexer **lex, char **str);
void					ft_handel_qoutes(t_lexer **lex, char **str);
int						ft_check_herdoc_fm(char *str);

// libft functions
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
char					*ft_itoa(int n);
int						ft_isalnum(int c);
int						ft_isalpha(int c);
t_lexer					*ft_lstnew(void *word, char type, int in_quotes);
void					ft_lstadd_back(t_lexer **lst, t_lexer *new);
int						ft_isdigit(int c);
void					*ft_memcpy(void *dest, const void *src, size_t n);
size_t					ft_strlen(const char *s);
char					*ft_strdup(const char *str);
void					*ft_calloc(size_t count, size_t size);
void					ft_bzero(void *s, size_t n);
void					*ft_memset(void *s, int c, size_t n);
char					*ft_strjoin(char *s1, char *s2);
t_parser				*ft_lst_new_prs(char **str, int in, int out);
void					ft_lstadd_back_prs(t_parser **lst, t_parser *new);
void					ft_lstclear(t_parser **lst);
void					ft_lstdelone(t_parser *lst);
void					ft_lstdelone_lex(t_lexer *lst);
void					ft_lstclear_lex(t_lexer **lst);
char					*ft_strjoin_char(char *s1, char s2);
int						ft_strcmp(char *s1, char *s2);
void					ft_putstr_fd(char const *s, int fd);
int						ft_strchr(char *str, char c);
int						ft_strncmp(char *s1, char *s2, int n);
char					**ft_split(char const *s, char c);
t_env					*ft_lstnew_env(void *name, void *val);
void					ft_lstadd_back_env(t_env **lst, t_env *new);
void					ft_free(char **str);
int						ft_atoi(const char *str);
void					ft_free_env(t_env **env);

// parsing
void					ft_parser(t_lexer *lex, t_parser **prs, char **env);
int						ft_fill_args(t_lexer *lex, t_parser **prs, char **env);
int						ft_check_in_out_snt(t_lexer *lex);
int						ft_count_heredoc(t_lexer *lex);
int						ft_count_arg(t_lexer *lex);
void					ft_inial(t_norm *var);
void					ft_use_heredoc(t_lexer **lex, char **env, int *fd);
void					ft_check_next_fd(t_lexer **lex, int in, int out);
void					ft_norm_herdoc(t_lexer *lex, char **env, char *hold,
							int fd);
char					*ft_hendel_var(char *val, char **av);
void					ft_handel_in(t_lexer **lex, int *in, char **av);
char					*ft_hendel_var_herdoc(char *val, char **av);
void					ft_fill_heredoc_fm(t_lexer **lex, int *in, int *out,
							char **av);
void					ft_norm_herdoc_norm(char **env, char *str, char *str1,
							int fd);
int						ft_norm_fill_args(t_lexer **lex, char **env, char **str,
							t_norm *var);
void					ft_join_var_word(t_lexer **lex, char **str, char **env,
							int i);
t_calcul				ft_inial_cal(void);
char					*ft_norm_hendle_var(char **av, char *val, t_calcul cl);
int						ft_check_other_var(char *var);
// excution
void					ft_excution(t_parser *pars, char **env, t_env **env_list);
void					ft_exc_cmd(t_parser *pars, char **env);
void					ft_red_out(t_parser *pars);
void					ft_red_in(t_parser *pars);
char					*ft_check_path(char *cmd, char **env);
void					rl_replace_line(const char *text, int clear_undo);
void					handel(int signal);
void					ft_status(void);
char					**ft_reconver(t_env *env);
int						ft_check_exit_args(char **args);
int						rl_catch_signals(int catch);
void					fill_env_list(char **env, t_env **env_list,
							t_parser *pars);
void					fill_empty_env(char **env, t_env **env_list);
void					ft_extra_handel(t_env **env_list, t_parser *pars,
							char *env);
int						ft_cnt_name(char *str);
char					*ft_norm_check_path(char *cmd, char *path);
void					ft_pipe(t_parser *pars, char **env, int fd[2], t_env **env_list);
void					ft_norm_exc(t_parser *pars, char **env, int fd[2],  t_env **env_list);
void					ft_dup_fd(t_parser *pars, int old, int fd[2]);

// builtins

int						ft_builtins(t_parser **prs, t_env **env_list);
void					ft_handel_echo(t_parser **prs);
int						ft_handel_n(char *str);
void					ft_handel_env(t_env **env);
void					ft_handel_pwd(t_env **env);
void					ft_chang_ocwd(t_env **env, char *old);
void					ft_chang_cwd(t_env **env, char *cur);
char					*get_home(t_env **env);
void					ft_handel_cd(t_parser **prs, t_env **env);
void					ft_write_error(int fd, char *str);
void					ft_print_exp(t_env **env);
void					ft_handel_export(t_parser **prs, t_env **env);

#endif

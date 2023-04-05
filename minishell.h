/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:59:09 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/04/03 22:19:32 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

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
	int					j;
	char				**str;
	char				*in;
	char				*out;
	int					*fd;
}						t_norm;

typedef struct s_parser
{
	char				**args;
	int					in_red;
	int					out_red;
	int					heredoc;
	struct s_parser		*next;
}						t_parser;

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}						t_env;

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
t_parser				*ft_lst_new_prs(char **str, int in, int out, int hdc);
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

// parsing
void					ft_parser(t_lexer *lex, t_parser **prs, char **env);
int						ft_fill_args(t_lexer *lex, t_parser **prs, char **env);
int						ft_check_in_out_snt(t_lexer *lex);
int						ft_count_heredoc(t_lexer *lex);
int						ft_count_arg(t_lexer *lex);
void					ft_inial(t_norm *var, t_lexer *lex);
void					ft_use_heredoc(t_lexer **lex, char **env, int *fd);
void					ft_check_next_fd(t_lexer *lex, int in, int out);
void					ft_norm_herdoc(t_lexer *lex, char **env, char *hold,
							int fd);
char					*ft_hendel_var(char *val, char **av);
char					*ft_hendel_var_herdoc(char *val, char **av);

//builtins
void					ft_builtins(t_parser **prs);
void					ft_handel_cd(t_parser **prs);
void					ft_handel_echo(t_parser **prs);
int						ft_handel_n(char *str);
#endif

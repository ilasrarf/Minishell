/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:59:09 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/03/19 18:15:59 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
char	*ft_strjoin(char const *s1, char const *s2);
// parsing
t_lexer    *ft_parser(t_lexer *lex);
#endif
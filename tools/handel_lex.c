/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_lex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:37:52 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/06/17 13:02:00 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_handel_char(t_lexer **lex, char **str)
{
	int		i;
	int		j;
	char	*hold;

	hold = ft_strdup("");
	i = 0;
	while ((*str)[i] && !ft_check_herdoc_fm(*str + i)
		&& !ft_strchr(" \t\n\r\v\f", (*str)[i]) && (*str)[i] != '|'
		&& (*str)[i] != '$' && (*str)[i] != '"' && (*str)[i] != '\'')
	{
		hold = ft_strjoin_char(hold, (*str)[i]);
		i++;
	}
	j = 0;
	while ((*str)[j] && j < i - 1 && (*str)[j] != '$'
		&& !ft_strchr(" \t\n\r\v\f", (*str)[j]))
		j++;
	if ((*str)[j] == '$')
		ft_lstadd_back(lex, ft_lstnew(hold, 'v', 0));
	else
		ft_lstadd_back(lex, ft_lstnew(hold, 'w', 0));
	*str += i;
}

void	ft_handel_var(t_lexer **lex, char **str)
{
	int	i;

	i = 0;
	i++;
	if ((*str)[i] == '_')
		i++;
	while ((*str)[i] && (!ft_strchr(" \t\n\r\v\f", (*str)[i])
			&& (*str)[i] != '\'' && (*str)[i] != '"' && (*str)[i] != '|'))
		i++;
	ft_lstadd_back(lex, ft_lstnew(ft_substr(*str, 0, i), 'v', 0));
	*str += i;
}

void	ft_handel_herdoc_fm(t_lexer **lex, char **str)
{
	int	i;

	i = 0;
	if ((*str)[i] == '<' && (*str)[i + 1] == '<')
	{
		ft_lstadd_back(lex, ft_lstnew(ft_strdup("<<"), 'h', 0));
		i += 2;
	}
	else if ((*str)[i] == '>' && (*str)[i + 1] == '>')
	{
		ft_lstadd_back(lex, ft_lstnew(ft_strdup(">>"), 'r', 0));
		i += 2;
	}
	else if ((*str)[i] == '<')
	{
		ft_lstadd_back(lex, ft_lstnew(ft_strdup("<"), 'r', 0));
		i++;
	}
	else if ((*str)[i] == '>')
	{
		ft_lstadd_back(lex, ft_lstnew(ft_strdup(">"), 'r', 0));
		i++;
	}
	*str += i;
}

int	ft_handel_dq(t_lexer **lex, char *str, int i)
{
	int	j;

	j = 0;
	i++;
	while (str[i] && str[i] != '"')
		i++;
	while (str[j] && str[j] != '$')
		j++;
	if (str[j] == '$' && j <= i)
		ft_lstadd_back(lex, ft_lstnew(ft_substr(str, 1, i - 1), 'v', 2));
	else
		ft_lstadd_back(lex, ft_lstnew(ft_substr(str, 1, i - 1), 'w', 2));
	i++;
	return (i);
}

void	ft_handel_qoutes(t_lexer **lex, char **str)
{
	int	i;

	i = 0;
	if ((*str)[i] == '"')
		i = ft_handel_dq(lex, *str, i);
	else if ((*str)[i] == '\'')
	{
		i++;
		while ((*str)[i] && (*str)[i] != '\'')
			i++;
		ft_lstadd_back(lex, ft_lstnew(ft_substr(*str, 1, i - 1), 'w', 1));
		i++;
	}
	*str += i;
}

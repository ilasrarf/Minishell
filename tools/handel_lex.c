/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_lex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:37:52 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/03/21 02:00:36 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_handel_char(t_lexer **lex, char **str)
{
	int	i;
	char *hold;

	hold = ft_strdup("");
	i = 0;
	while ((*str)[i] && !ft_check_herdoc_fm(*str + i) && (*str)[i] != ' '
		&& (*str)[i] != '|' && (*str)[i] != '$')
	{
		if((*str)[i] != '"' && (*str)[i] != '\'')
			hold = ft_strjoin_char(hold , (*str)[i]);
		i++;
	}
	ft_lstadd_back(lex, ft_lstnew(hold,'w',0));
	*str += i;
}

void	ft_handel_var(t_lexer **lex, char **str)
{
	int	i;

	i = 0;
	i++;
	if ((*str)[i] == '_')
	{
		i++;
		while ((*str)[i] && ft_isalnum((*str)[i]))
			i++;
		ft_lstadd_back(lex, ft_lstnew(ft_substr(*str, 0, i),'v',0));
	}
	else
	{
		while ((*str)[i] && ft_isalpha((*str)[i]))
			i++;
		ft_lstadd_back(lex, ft_lstnew(ft_substr(*str, 0, i),'v',0));
	}
	*str += i;
}

void	ft_handel_herdoc_fm(t_lexer **lex, char **str)
{
	int	i;

	i = 0;
	if ((*str)[i] == '<' && (*str)[i + 1] == '<')
	{
		ft_lstadd_back(lex, ft_lstnew(ft_strdup("<<"),'h',0));
		i += 2;
	}
	else if ((*str)[i] == '>' && (*str)[i + 1] == '>')
	{
		ft_lstadd_back(lex, ft_lstnew(ft_strdup(">>"),'a',0));
		i += 2;
	}
	else if ((*str)[i] == '<')
	{
		ft_lstadd_back(lex, ft_lstnew(ft_strdup("<"),'i',0));
		i++;
	}
	else if ((*str)[i] == '>')
	{
		ft_lstadd_back(lex, ft_lstnew(ft_strdup(">"),'o',0));
		i++;
	}
	*str += i;
}

void	ft_handel_qoutes(t_lexer **lex, char **str)
{
	int	i;

	i = 0;
	if ((*str)[i] == '"')
	{
		i++;
		while ((*str)[i] != '"')
			i++;
		ft_lstadd_back(lex, ft_lstnew(ft_substr(*str, 1, i - 1),'w',2));
		i++;
	}
	else
	{
		i++;
		while ((*str)[i] != '\'')
			i++;
		ft_lstadd_back(lex, ft_lstnew(ft_substr(*str, 1, i - 1),'w',1));
		i++;
	}
	*str += i;
}
// void	ft_handel_extra(t_lexer **lex, char **str)
// {
// 	int	i;

// 	i = 0;
// 	while ((*str)[i])
// 	{

// 	}

// }

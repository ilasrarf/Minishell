/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexeing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:57:32 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/03/29 21:19:02 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_herdoc_fm(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '<' && str[i + 1] == '<')
		return (1);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (1);
	else if (str[i] == '<')
		return (1);
	else if (str[i] == '>')
		return (1);
	return (0);
}

int	ft_check_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i] != '\'')
				return (1);
		}
		else if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
			if (str[i] != '"')
				return (1);
		}
		i++;
	}
	return (0);
}

void	ft_lexer(char *str, t_lexer **lex)
{
	*lex = NULL;
	while (*str)
	{
		if (!ft_check_herdoc_fm(str) && *str != ' ' && *str != '|'
			&& *str != '$')
			ft_handel_char(lex, &str);
		else if (*str == ' ')
		{
			ft_lstadd_back(lex, ft_lstnew(ft_strdup(" "), 's', 0));
			while (*str && *str == ' ')
				str++;
		}
		if (*str == '$')
			ft_handel_var(lex, &str);
		else if (*str == '|')
		{
			ft_lstadd_back(lex, ft_lstnew(ft_strdup("|"), 'p', 0));
			str++;
		}
		else if (ft_check_herdoc_fm(str))
			ft_handel_herdoc_fm(lex, &str);
		else if (*str == '\'' || *str == '"')
			ft_handel_qoutes(lex, &str);
	}
}

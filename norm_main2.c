/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_main2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 13:43:15 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/06/21 21:48:21 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_norm_handel(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_kk(t_lexer **lex, t_norm *var, char **env, char **str)
{
	while ((*lex) && g_var->suspend != 0)
	{
		if ((*lex) && (*lex)->type == 'p')
		{
			g_var->index++;
			break ;
		}
		if (ft_norm_fill_args(lex, env, str, var))
		{
			if (str[var->i])
				var->i++;
		}
		if ((*lex) && (*lex)->type == 's')
			(*lex) = (*lex)->next;
	}
}

void	ft_norm_handel_var(char **env, char *var, char **exp, int j)
{
	char	*hold;

	if (var + j)
		*exp = ft_strjoin(*exp, var + j);
	while (var[j] && var[j] != '$')
		j++;
	if (var[j] == '$')
	{
		hold = *exp;
		*exp = ft_hendel_var(NULL, *exp, env);
		free(hold);
	}
}

char	*ft_norm_handel_var2(char **env, char *var, int *i, int *j)
{
	while (var[*j] && (ft_isalnum(var[*j]) || var[*j] == '_'))
		(*j)++;
	if (var[*i] == '?')
	{
		(*j)++;
		return (ft_itoa(g_var->exit_s));
	}
	else
		return (ft_expande(env, ft_substr(var, *i, (*j) - (*i)), (*j) - (*i)));
}

char	*ft_join_args(t_lexer **lex, char **str, char **env, int i)
{
	char	*str1;

	if ((*lex)->type == 'v')
	{
		str1 = ft_hendel_var(*lex, (*lex)->word, env);
		if (!str[i])
			str[i] = ft_strdup(str1);
		else
			str[i] = ft_strjoin(str[i], str1);
		free(str1);
	}
	else if (str[i])
		str[i] = ft_strjoin(str[i], (*lex)->word);
	else
		str[i] = ft_strdup((*lex)->word);
	(*lex) = (*lex)->next;
	return (str[i]);
}

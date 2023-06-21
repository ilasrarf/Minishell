/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_tools1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 02:12:02 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/06/22 00:00:33 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_next_fd(t_lexer *lex, int in, int out, char **env)
{
	char	*str;

	if (in == -1 || out == -1)
		ft_write_error_exc(": No such file or directory\n", (lex)->word);
	if (in == -3 || out == -3)
	{
		str = ft_hendel_var(lex, lex->word, env);
		ft_write_error_exc(": No such file or directory\n", str);
		free(str);
	}
	else if (in == -2 || out == -2)
		ft_write_error_exc(": ambiguous redirect\n", (lex)->word);
	else
	{
		(lex) = (lex)->next;
		while (lex && (lex)->type != 'p')
		{
			if ((!ft_strcmp((lex)->word, ">") || !ft_strcmp((lex)->word, ">>"))
				&& out >= 3)
				close(out);
			else if (!ft_strcmp((lex)->word, "<") && in >= 3)
				close(in);
			(lex) = (lex)->next;
		}
	}
}

void	ft_norm_herdoc(t_lexer **lex, char **env, char *hold, int *fd)
{
	char	*str;
	char	*str1;

	str = NULL;
	str1 = NULL;
	g_var->fd_hd = *fd;
	while (lex && g_var->suspend)
	{
		g_var->in_hdc = 1;
		if (ft_fill_herdoc(lex, env, hold, fd))
			break ;
	}
	g_var->in_hdc = 0;
}

int	ft_check_other_var(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '\'')
		i++;
	if (var[i] == '\'')
		return (0);
	i = 0;
	while (var[i] && var[i] != '$')
		i++;
	if (var[i] == '$')
		return (1);
	return (0);
}

char	*join_befor_var(char *exp, char *var, int i)
{
	char	*hold;

	hold = exp;
	if (var[i - 1] == '$' && !var[i])
		exp = ft_strjoin(ft_substr(var, 0, i), exp);
	else
		exp = ft_strjoin(ft_substr(var, 0, i - 1), exp);
	free(hold);
	return (exp);
}

char	*ft_hendel_var(t_lexer *lex, char *var, char **env)
{
	int		i;
	char	*exp;
	int		j;

	i = 0;
	j = 0;
	if (var[i] == '$' && !var[i + 1] && lex && lex->next
		&& lex->next->in_quotes)
		return (ft_strdup(""));
	while (var[i] && var[i] != '$')
		i++;
	i++;
	if (!var[i])
		return (ft_strdup("$"));
	j = i;
	exp = ft_norm_handel_var2(env, var, &i, &j);
	if (i > 1)
		exp = join_befor_var(exp, var, i);
	ft_norm_handel_var(env, var, &exp, j);
	return (exp);
}

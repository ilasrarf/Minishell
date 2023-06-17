/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_tools1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 02:12:02 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/06/17 13:42:19 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_next_fd(t_lexer *lex, int in, int out, char **env)
{
	char	*str;

	if (in == -1)
		ft_write_error_exc(": No such file or directory\n", (lex)->word);
	if (in == -3 || out == -3)
	{
		str = ft_hendel_var(lex->word, env);
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

void	ft_norm_herdoc(t_lexer *lex, char **env, char *hold, int *fd)
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
	// if (lex && ft_strcmp(g_var->str, lex->word))
	// 	ft_close_open_herdoc(hold, &fd);
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

char	*ft_expande(char **env, char *var, int len)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strcmp(env[i], var))
		{
			free(var);
			return (ft_strdup(env[i] + len + 1));
		}
		i++;
	}
	free(var);
	return (ft_strdup(""));
}

char	*ft_hendel_var(char *var, char **env)
{
	int		i;
	char	*exp;
	char	*hold;
	int		j;

	i = 0;
	j = 0;
	while (var[i] && var[i] != '$')
		i++;
	i++;
	if (!var[i])
		return (ft_strdup("$"));
	j = i;
	while (var[j] && (ft_isalnum(var[j]) || var[j] == '_'))
		j++;
	if (var[i] == '?')
	{
		j++;
		exp = ft_itoa(g_var->exit_s);
	}
	else
		exp = ft_expande(env, ft_substr(var, i, j - i), j - i);
	if (i > 1)
	{
		hold = exp;
		exp = ft_strjoin(ft_substr(var, 0, i - 1), exp);
		free(hold);
	}
	if (var + j)
		exp = ft_strjoin(exp, var + j);
	while (var[j] && var[j] != '$')
		j++;
	if (var[j] == '$')
	{
		hold = exp;
		exp = ft_hendel_var(exp, env);
		free(hold);
	}
	return (exp);
}

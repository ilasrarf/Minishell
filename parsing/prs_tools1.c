/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_tools1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 02:12:02 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/06/20 15:40:05 by aen-naas         ###   ########.fr       */
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

char	*ft_expande(char **env, char *var, int len)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (my_strcmp(env[i], var))
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
	exp = ft_norm_handel_var2(env, var, &i, &j);
	if (i > 1)
	{
		hold = exp;
		exp = ft_strjoin(ft_substr(var, 0, i - 1), exp);
		free(hold);
	}
	ft_norm_handel_var(env, var, &exp, j);
	return (exp);
}

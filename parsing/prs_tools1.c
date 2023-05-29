/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_tools1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 02:12:02 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/05/29 17:54:25 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_next_fd(t_lexer *lex, int in, int out)
{
	if (in == -1)
		printf("minishell: %s: No such file or directory\n", (lex)->word);
	else if (in == -2)
		printf("minishell: %s: ambiguous redirect\n", (lex)->word);
	else
	{
		fprintf(stderr, "test\n");
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

void	heredoc_sgl(int signal)
{
	if (signal == SIGINT)
	{
		g_var->suspend = 0;
		g_var->i = dup(STDIN_FILENO);
		close(0);
	}
	else
		return ;
}

void	ft_norm_herdoc(t_lexer *lex, char **env, char *hold, int fd)
{
	char	*str;
	char	*str1;

	str = NULL;
	str1 = NULL;
	signal(SIGINT, &heredoc_sgl);
	while (lex)
	{
		if (ft_fill_herdoc(lex, env, hold, fd))
			break ;
	}
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

char	*ft_hendel_var(char *val, char **av)
{
	t_calcul	cl;

	cl = ft_inial_cal();
	while (val[cl.j] && val[cl.j] != '$')
		cl.j++;
	if (val[cl.j + 1] == '?')
	{
		return (ft_itoa(g_var->exit_s));
	}
	cl.len = cl.j + 1;
	while (val[cl.len] && (val[cl.len] == '_' || ft_isalnum(val[cl.len])))
		cl.len++;
	cl.len -= cl.j;
	while (av[cl.i])
	{
		cl.k = 0;
		while (av[cl.i] && av[cl.i][cl.k] != '=')
			cl.k++;
		if (!ft_strncmp(av[cl.i], val + cl.j + 1, cl.k) && !ft_strncmp(av[cl.i],
				val + cl.j + 1, cl.len - 1))
			break ;
		cl.i++;
	}
	return (ft_norm_hendle_var(av, val, cl));
}

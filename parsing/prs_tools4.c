/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_tools4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 21:14:50 by aen-naas          #+#    #+#             */
/*   Updated: 2023/06/12 11:58:55 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_herdoc_sig(int *i)
{
	(void)i;
	if (g_var->str)
		ft_free_char(&g_var->str);
	g_var->suspend = 0;
	g_var->exit_s = 1;
	g_var->i = dup(STDIN_FILENO);
	close(0);
	g_var->in_hdc = 0;
}

void	ft_sigdef(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int count_pipe(t_lexer *lex)
{
	int i;
	
	i = 0;
	while (lex)
	{
		if (lex->type == 'p')
			i++;
		lex = lex->next;
	}
	return (i);	
}

void	ft_heredoc_first(t_lexer *lex, int *fd, char **env)
{
	int i;

	i = 0;
	while (lex)
	{
		if (lex && lex->type == 'p')
			i++;
		if (lex && !ft_strcmp(lex->word, "<<") && lex->type == 'r')
			ft_use_heredoc(&lex, env, &fd[i]);
		if (lex)
			lex = lex->next;
	}
}

char	**ft_realloc(char *holder, char **str)
{
	char **res;
	char **new;
	int i = 0;
	int j = 0;

	res = ft_split_white(holder);
	while (res[i])
		i++;
	if (i == 1)
	{
		ft_free(res);
		return str;
	}
	new = (char **)ft_calloc((i + g_var->size) , sizeof(char *));
	i = 0;
	while (str[j])
	{
		new[j] = ft_strdup(str[j]);
		j++;
	}
	while (res[i])
	{
		new[j] = res[i];
		j++;
		i++;
	}
	free(res);
	return new;
}

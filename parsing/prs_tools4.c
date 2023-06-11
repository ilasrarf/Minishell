/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_tools4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 21:14:50 by aen-naas          #+#    #+#             */
/*   Updated: 2023/06/09 22:10:47 by ilasrarf         ###   ########.fr       */
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

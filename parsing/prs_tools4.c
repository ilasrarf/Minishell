/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_tools4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 21:14:50 by aen-naas          #+#    #+#             */
/*   Updated: 2023/06/08 18:29:42 by ilasrarf         ###   ########.fr       */
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

void	ft_create_list(t_parser **prs, t_lexer *lex)
{
	int i;

	i = 0;
	while (lex)
	{
		if (lex->type == 'p')
			i++;
		lex = lex->next;
	}
	while (i >= 0)
	{
		ft_lstadd_back_prs(prs, ft_lst_new_prs(NULL, 0, 0));
		i--;
	}
}

void	ft_herdoc_fisrt(t_parser **prs, t_lexer *lex, char **env)
{
	int	in;

	in = 0;
	while (lex)
	{
		if (lex && !ft_strcmp(lex->word, "<<") && lex->type == 'r')
		{
			ft_use_heredoc(&lex, env, &in);
			(*prs)->in_red = in;
			g_var->fd = in;
		}
		if (lex && lex->type == 'p')
		{
			if (*prs)
			{
				(*prs) = (*prs)->next;
				in = 0;
			}
		}
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
	new = (char **)ft_calloc((i + g_var->size) + 1, sizeof(char *));
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
	return new;
}

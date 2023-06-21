/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_tools4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 21:14:50 by aen-naas          #+#    #+#             */
/*   Updated: 2023/06/21 14:09:54 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_herdoc_sig(void)
{
	if (g_var->str)
		ft_free_char(&g_var->str);
	g_var->suspend = 0;
	g_var->exit_s = 1;
	g_var->i = dup(STDIN_FILENO);
	g_var->in_hdc = 0;
	if (g_var->fd_hd > 2)
		close(g_var->fd_hd);
	close(0);
}

void	ft_sigdef(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	count_pipe(t_lexer *lex)
{
	int	i;

	i = 0;
	while (lex)
	{
		if (lex->type == 'p')
			i++;
		lex = lex->next;
	}
	if (!i)
		i++;
	return (i);
}

void	ft_heredoc_first(t_lexer *lex, int *fd, char **env)
{
	int	i;

	i = 0;
	while (lex)
	{
		if (lex && lex->type == 'h')
		{
			if (fd[i])
				close(fd[i]);
			ft_use_heredoc(&lex, env, &fd[i]);
		}
		if (lex && (lex->type != 'h'))
		{
			if (lex->type == 'p')
				i++;
			lex = lex->next;
		}
	}
}

char	**ft_realloc(char *holder, char **str)
{
	char	**res;
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = ft_split_white(holder);
	while (res[i])
		i++;
	if (i == 1)
		return (ft_free(res), str);
	new = (char **)ft_calloc((i + g_var->size), sizeof(char *));
	i = 0;
	while (str[j])
	{
		new[j] = ft_strdup(str[j]);
		j++;
	}
	while (res[i])
		new[j++] = res[i++];
	free(res);
	return (new);
}

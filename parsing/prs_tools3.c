/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_tools3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:20:43 by aen-naas          #+#    #+#             */
/*   Updated: 2023/05/30 12:50:43 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_norm_fill_args(t_lexer **lex, char **env, char **str, t_norm *var)
{
	if ((*lex) && (*lex)->type == 'p')
		return (1);
	if ((*lex) && (!ft_strcmp((*lex)->word, ">") || !ft_strcmp((*lex)->word,
				"<") || !ft_strcmp((*lex)->word, ">>")) && (*lex)->type == 'r')
		ft_fill_heredoc_fm(&(*lex), &var->in, &var->out, env);
	if ((*lex) && !ft_strcmp((*lex)->word, "<<") && (*lex)->type == 'r')
		ft_use_heredoc(&(*lex), env, &var->in);
	if ((*lex) && ((*lex)->type == 'v' || (*lex)->type == 'w'))
	{
		ft_join_var_word(lex, str, env, var->i);
		return (1);
	}
	return (0);
}

void	ft_handel_in(t_lexer **lex, int *in, char **av)
{
	(void)av;
	if ((*lex)->type != 'v')
		*in = open((*lex)->word, O_RDONLY, 0777);
	else
	{
		*in = open(ft_hendel_var((*lex)->word, av), O_RDONLY, 0777);
		if (*in < 0)
			*in = -2;
	}
}

int	ft_fill_herdoc(t_lexer *lex, char **env, char *hold, int fd)
{
	g_var->str = readline("\e[91mheredoc>  \e[0m");
	if (!ft_strcmp(g_var->str, lex->word))
	{
		free(g_var->str);
		return (1);
	}
	if (!g_var->str)
	{
		close(fd);
		return (1);
	}
	if (lex->in_quotes == 0 && ft_strchr(g_var->str, '$'))
		ft_norm_herdoc_norm(env, g_var->str, fd);
	else if (ft_strcmp(g_var->str, lex->word))
	{
		ft_putstr_fd(g_var->str, fd);
		write(fd, "\n", 1);
		close(fd);
		fd = open(hold, O_RDWR | O_CREAT | O_APPEND, 0777);
	}
	if (g_var->str)
	{
		free(g_var->str);
		g_var->str = NULL;
	}
	return (0);
}

void	ft_handel_open_error(int in, int out, t_lexer **lex)
{
	if (in == -1 && *lex)
	{
		while ((*lex)->next)
		{
			if ((*lex)->next->type == 'p')
				break ;
			*lex = (*lex)->next;
		}
	}
	else if (out == -1 && (*lex)->word[0] == '/')
		ft_write_error_exc(": Permission denied\n", (*lex)->word);
}

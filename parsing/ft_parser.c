/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:23:37 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/06/16 23:15:45 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_out_open(t_lexer **lex, char **out_red)
{
	*lex = (*lex)->next;
	if (!ft_strcmp((*lex)->word, " "))
		*lex = (*lex)->next;
	free(*out_red);
	*out_red = ft_strdup((*lex)->word);
	return (open((*lex)->word, O_CREAT | O_RDWR, 0777));
}

int	ft_check_syntax(t_lexer *lex)
{
	while (lex)
	{
		if (lex->type != 's')
			break ;
		lex = lex->next;
	}
	if (lex && !ft_strcmp(lex->word, "|") && lex->type == 'p')
		return (0);
	while (lex)
	{
		if (!ft_strcmp(lex->word, "|") && lex->type == 'p')
		{
			if (lex->next && lex->next->type == 's')
				lex = lex->next;
			if ((lex->next && lex->next->type == 'p') || !lex->next)
				return (0);
		}
		lex = lex->next;
	}
	return (1);
}

void	ft_fill_heredoc_fm(t_lexer **lex, int *in, int *out, char **av)
{
	if (!ft_strcmp((*lex)->word, "<"))
	{
		(*lex) = (*lex)->next;
		if (!ft_strcmp((*lex)->word, " "))
			(*lex) = (*lex)->next;
		ft_open_red(lex, in, av, 0);
	}
	else if (!ft_strcmp((*lex)->word, ">"))
	{
		(*lex) = (*lex)->next;
		if (!ft_strcmp((*lex)->word, " "))
			(*lex) = (*lex)->next;
		ft_open_red(lex, out, av, 2);
	}
	else if (!ft_strcmp((*lex)->word, ">>"))
	{
		(*lex) = (*lex)->next;
		if (!ft_strcmp((*lex)->word, " "))
			(*lex) = (*lex)->next;
		ft_open_red(lex, out, av, 1);
	}
	ft_check_next_fd(*lex, *in, *out, av);
	ft_handel_open_error(*in, *out, lex);
	if (*lex)
		(*lex) = (*lex)->next;
}

int	ft_fill_args(t_lexer *lex, t_parser **prs, char **env, int *fd)
{
	char	**str;
	t_norm	var;

	ft_inial(&var);
	var.fd = fd;
	var.i = ft_count_arg(lex);
	g_var->size = var.i;
	str = ft_calloc(var.i + 1, sizeof(char *));
	var.i = 0;
	ft_kk(&lex, &var, env, str);
	if (g_var->relock)
	{
		ft_free(str);
		str = g_var->relock;
		g_var->relock = NULL;
	}
	ft_lstadd_back_prs(prs, ft_lst_new_prs(str, var.in, var.out));
	if (lex && !ft_strcmp(lex->word, "|"))
	{
		lex = lex->next;
		str = NULL;
		ft_fill_args(lex, prs, env, fd);
	}
	return (0);
}

void	ft_parser(t_lexer *lex, t_parser **prs, char **env)
{
	t_lexer	*lex1;
	int		i;
	int		*fd;

	i = count_pipe(lex);
	lex1 = lex;
	fd = malloc(sizeof(int) * i);
	g_var->fd = fd;
	*prs = NULL;
	if (!lex || !ft_check_syntax(lex) || !ft_check_in_out_snt(lex))
	{
		if (!ft_check_syntax(lex))
		{
			ft_putstr_fd("parssing error in pipe\n", 2);
			g_var->exit_s = 2;
		}
		return ;
	}
	ft_heredoc_first(lex1, fd, env);
	g_var->index = 0;
	ft_fill_args(lex, prs, env, fd);
	g_var->index = 0;
	t_parser *hold = *prs;
	i = 0;
	while (hold)
	{
		printf("in :%d\n", hold->in_red);
		hold = hold->next;
	}
	
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:23:37 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/05/24 18:31:31 by aen-naas         ###   ########.fr       */
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
		ft_handel_in(lex, in, av);
	}
	else if (!ft_strcmp((*lex)->word, ">"))
	{
		(*lex) = (*lex)->next;
		if (!ft_strcmp((*lex)->word, " "))
			(*lex) = (*lex)->next;
		*out = open((*lex)->word, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	}
	else if (!ft_strcmp((*lex)->word, ">>"))
	{
		(*lex) = (*lex)->next;
		if (!ft_strcmp((*lex)->word, " "))
			(*lex) = (*lex)->next;
		*out = open((*lex)->word, O_WRONLY | O_CREAT, 0777);
	}
	ft_check_next_fd(lex, *in, *out);
	if (*lex)
		(*lex) = (*lex)->next;
}

int	ft_fill_args(t_lexer *lex, t_parser **prs, char **env)
{
	char	**str;
	t_norm	var;

	ft_inial(&var);
	var.i = ft_count_arg(lex);
	str = ft_calloc(var.i + 1, sizeof(char *));
	var.i = 0;
	while (lex)
	{
		if (lex && lex->type == 'p')
			break ;
		if (ft_norm_fill_args(&lex, env, str, &var))
			var.i++;
		if (lex && lex->type != 'p')
			lex = lex->next;
	}
	str[var.i] = NULL;
	ft_lstadd_back_prs(prs, ft_lst_new_prs(str, var.in, var.out));
	if (lex && !ft_strcmp(lex->word, "|"))
	{
		lex = lex->next;
		str = NULL;
		ft_fill_args(lex, prs, env);
	}
	return (0);
}

void	ft_parser(t_lexer *lex, t_parser **prs, char **env)
{
	t_parser	*holder;

	*prs = NULL;
	if (!lex || !ft_check_in_out_snt(lex) || !ft_check_syntax(lex))
		return ;
	ft_fill_args(lex, prs, env);
	holder = *prs;
}

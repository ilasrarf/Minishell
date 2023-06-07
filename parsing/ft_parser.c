/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:23:37 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/06/07 12:43:46 by aen-naas         ###   ########.fr       */
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
		*out = open((*lex)->word, O_WRONLY | O_CREAT | O_APPEND, 0777);
	}
	ft_check_next_fd(*lex, *in, *out);
	ft_handel_open_error(*in, *out, lex);
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
	while (lex && g_var->suspend != 0)
	{
		if (lex && lex->type == 'p')
		{
			(*prs)->args = str;
			(*prs)->out_red = var.out;
			(*prs) = (*prs)->next;
			lex = lex->next;
			ft_inial(&var);
			var.i = ft_count_arg(lex);
			str = ft_calloc(var.i + 1, sizeof(char *));
			var.i = 0;
		}
		if (ft_norm_fill_args(&lex, env, str, &var))
		{
			(*prs)->args = str;
			(*prs)->out_red = var.out;
			(*prs)->in_red = var.in;
			if (!lex)
				break;
		}
		if (lex && lex->type == 's')
			lex = lex->next;
	}
	return (0);
}

void	ft_parser(t_lexer *lex, t_parser **prs, char **env)
{
	t_parser	*holder;

	*prs = NULL;
	(void)env;
	if (!lex || !ft_check_in_out_snt(lex) || !ft_check_syntax(lex))
	{
		if (!ft_check_syntax(lex))
			ft_putstr_fd("parssing error in pipe\n", 2);
		return ;
	}
	ft_create_list(prs, lex);
	holder = *prs;
	ft_herdoc_fisrt(prs, lex, env);
	*prs = holder;
	ft_fill_args(lex, prs, env);
	// *prs = holder;
	// printf("\n-------------\n");
	// int			i = 0;
	// while(holder)
	// {
	//     i = 0;
	//     while (holder->args && holder->args[i])
	//     {
	//         printf("ARGS: %s\n",holder->args[i]);
	//         i++;
	//     }
	// 	printf("in %i\n", holder->in_red);
	// 	printf("out %i\n", holder->out_red);
	//     holder = holder->next;
	// 	printf("\n-------------\n");
	// }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:23:37 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/05/21 11:34:43 by aen-naas         ###   ########.fr       */
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

int	ft_fill_heredoc_fm(t_lexer **lex, int *in, int *out)
{
	if (!ft_strcmp((*lex)->word, "<"))
	{
		(*lex) = (*lex)->next;
		if (!ft_strcmp((*lex)->word, " "))
			(*lex) = (*lex)->next;
		*in = open((*lex)->word, O_RDONLY, 0777);
		if (*in < 0)
			printf("minisell: %s: No such file or directory\n", (*lex)->word);
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
	if (*lex)
		(*lex) = (*lex)->next;
	ft_check_next_fd(*lex, *in, *out);
	return (0);
}

int	ft_fill_args(t_lexer *lex, t_parser **prs, char **env)
{
	int		i;
	char	**str;
	int		in;
	int		out;

	i = ft_count_arg(lex);
	str = ft_calloc(i + 1, sizeof(char *));
	// printf("set index: %i\n", i + 1);
	i = 0;
	in = 0;
	out = 0;
	while (lex)
	{
		if (lex && lex->type == 'p')
			break ;
		if (lex && (!ft_strcmp(lex->word, ">") || !ft_strcmp(lex->word, "<")
				|| !ft_strcmp(lex->word, ">>")))
			ft_fill_heredoc_fm(&lex, &in, &out);
		if (lex && !ft_strcmp(lex->word, "<<"))
			ft_use_heredoc(&lex, env, &in);
		if (lex && lex->type == 'v')
		{
			str[i] = ft_hendel_var(lex->word, env);
			i++;
		}
		if (lex && lex->type == 'w')
		{
			str[i] = ft_strdup(lex->word);
			i++;
		}
		if (lex && lex->type != 'p')
			lex = lex->next;
	}
	// printf("last index %i\n", i);
	str[i] = NULL;
	ft_lstadd_back_prs(prs, ft_lst_new_prs(str, in, out));
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
	// printf("\n-------------\n");
	// int			i = 0;
	// while(holder)
    // {
    //     i = 0;
    //     while (holder->args[i])
    //     {
    //         printf("ARGS: %s\n",holder->args[i]);
    //         i++;
    //     }
	// 	printf("in %i\n", holder->in_red);
	// 	printf("out %i\n", holder->out_red);
    //     holder = holder->next;
    // } 
	ft_lstclear_lex(&lex);
}

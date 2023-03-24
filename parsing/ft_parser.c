/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:23:37 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/03/24 00:29:08 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_arg(t_lexer *lex)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (lex)
	{
		if ((lex->word[0] == '|' && lex->in_quotes == 0))
			return (i - j);
		if (lex->word[0] != ' ')
			i++;
		if (ft_check_herdoc_fm(lex->word))
			j++;
		lex = lex->next;
	}
	return (i - j);
}



int    *ft_fill_heredoc_fm(t_lexer **lex, char **in_red, char **out_red, int n)
{
    static int	i;
	static int	*fd;

	if (!fd)
		fd = ft_calloc(n + 1, sizeof(int));
	if (!ft_strcmp((*lex)->word, ">"))
	{
		*lex = (*lex)->next;
		if (!ft_strcmp((*lex)->word, " "))
			*lex = (*lex)->next;
		if (n == 1 || i == n)
			*out_red = ft_strdup((*lex)->word);
		fd[i] = open((*lex)->word, O_CREAT | O_RDWR, 0777);
	}
	else
	{
		*lex = (*lex)->next;
		if (*lex && !ft_strcmp((*lex)->word, " "))	
			*lex = (*lex)->next;
		if (n == 1)
			*in_red = ft_strdup((*lex)->word);
		else if (i == n && n != 1)
		fd[i] = open((*lex)->word, O_CREAT | O_RDWR, 0777);
	}
	i++;
	return (fd);
}

void	ft_fill_args(t_lexer *lex, t_parser **prs)
{
	int		i;
	int		j;
	char	**str;
	static char	*in;
	static char	*out;
	int		*fd;

	i = ft_count_arg(lex);
	str = ft_calloc(i + 1 , sizeof(char *));
	i = ft_count_heredoc(lex);
	j = 0;
	while (lex)
	{
		if (!ft_strcmp(lex->word, "|") && lex->in_quotes == 0)
			break ;
        if (!ft_strcmp(lex->word, ">") || !ft_strcmp(lex->word, "<"))
        	fd = ft_fill_heredoc_fm(&lex, &in, &out, i);
		else if (lex && ft_strcmp(lex->word, " "))
		{
			str[j] = ft_strdup(lex->word);
			j++;
		}
		if (lex)
			lex = lex->next;
	}
	ft_lstadd_back_prs(prs, ft_lst_new_prs(str,in ,out, fd));
	if (lex && !ft_strcmp(lex->word, "|"))
	{
		lex = lex->next;
		ft_fill_args(lex, prs);
	}
}

void	ft_parser(t_lexer *lex, t_parser **prs)
{
	t_parser	*holder;

	*prs = NULL;
	if(!ft_check_in_out_snt(lex))
		return ;
	ft_fill_args(lex, prs);
	holder = (*prs);
	int			i;
	while (holder)
	{
		i = 0;
		while (holder->args[i])
		{
			printf("args -> %s\n", holder->args[i]);
			i++;
		}
		printf("in -> %s\n", holder->in_red);
		printf("out -> %s\n", holder->out_red);
		i = 0;
		while (holder->fd[i])
		{
			printf("fd -> %d\n", holder->fd[i]);
			i++;
		}
		printf("---------\n");
		holder = holder->next;
	}
	// ft_lstclear_lex(&lex);
	// ft_lstclear(prs);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:23:37 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/06/15 14:58:33 by aen-naas         ###   ########.fr       */
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
	str[var.i] = NULL;
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
	t_parser	*holder;
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
	// write(fd[0], "out\n", 4);
	g_var->index = 0;
	ft_fill_args(lex, prs, env, fd);
	// write((*prs)->in_red, "in\n", 3);
	g_var->index = 0;
	holder = *prs;
	// printf("\n-------------\n");
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

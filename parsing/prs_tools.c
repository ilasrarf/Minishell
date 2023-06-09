/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 21:16:02 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/06/20 15:39:47 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_in_out_snt(t_lexer *lex)
{
	while (lex)
	{
		if (lex && (lex->type == 'r' || lex->type == 'h'))
		{
			if (lex->next && !ft_strcmp(lex->next->word, " "))
				lex = lex->next;
			if (!lex->next || (lex->next->type != 'w'
					&& lex->next->type != 'v'))
			{
				if (lex->next)
					lex = lex->next;
				g_var->exit_s = 258;
				ft_putstr_fd("syntax error near unexpected token `", 2);
				ft_putstr_fd(lex->word, 2);
				ft_putstr_fd("`\n", 2);
				return (0);
			}
		}
		lex = lex->next;
	}
	return (1);
}

int	ft_count_heredoc(t_lexer *lex)
{
	int	i;

	i = 0;
	while (lex)
	{
		if (!ft_strcmp(lex->word, "|") && lex->type == 'p')
			break ;
		if (!ft_strcmp(lex->word, ">") || !ft_strcmp(lex->word, "<"))
			i++;
		lex = lex->next;
	}
	return (i);
}

int	ft_count_arg(t_lexer *lex)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (lex)
	{
		if (lex->type == 'p')
			return (i - j);
		if (lex->type == 'w' || lex->type == 'v')
			i++;
		if (lex->type == 'r' || lex->type == 'h')
			j++;
		lex = lex->next;
	}
	return (i - j);
}

void	ft_inial(t_norm *var)
{
	var->i = 0;
	var->in = 1;
	var->out = 1;
}

void	ft_use_heredoc(t_lexer **lex, char **env, int *fd)
{
	char		*hold;
	char		*hold1;
	static int	i;

	hold1 = ft_itoa(i);
	hold = ft_strjoin(ft_strdup("/tmp/heredoc_"), hold1);
	while (!access(hold, F_OK))
	{
		free(hold);
		free(hold1);
		hold1 = ft_itoa(i);
		i++;
		hold = ft_strjoin(ft_strdup("/tmp/heredoc_"), hold1);
	}
	free(hold1);
	if (*lex)
		*lex = (*lex)->next;
	if ((*lex) && !ft_strcmp((*lex)->word, " "))
		*lex = (*lex)->next;
	*fd = open(hold, O_RDWR | O_CREAT, 0777);
	i++;
	ft_norm_herdoc(lex, env, hold, fd);
	free(hold);
	if (*lex)
		(*lex) = (*lex)->next;
}

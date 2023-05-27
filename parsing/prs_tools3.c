/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_tools3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:20:43 by aen-naas          #+#    #+#             */
/*   Updated: 2023/05/27 16:38:32 by aen-naas         ###   ########.fr       */
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
	// else
	// {
	// 	*in = open(ft_hendel_var((*lex)->word ,av), O_RDONLY, 0777);
	// 	if (*in < 0)
	// 		*in = -2;
	// }
}

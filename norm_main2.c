/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_main2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 13:43:15 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/06/12 15:39:53 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_norm_handel(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_kk(t_lexer **lex, t_norm *var, char **env, char **str)
{
	while ((*lex) && g_var->suspend != 0)
	{
		if ((*lex) && (*lex)->type == 'p')
		{
			g_var->index++;
			break ;
		}
		if (ft_norm_fill_args(lex, env, str, var))
			var->i++;
		if ((*lex) && (*lex)->type == 's')
			(*lex) = (*lex)->next;
	}
}

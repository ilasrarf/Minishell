/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_main2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 13:43:15 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/06/16 21:03:49 by ilasrarf         ###   ########.fr       */
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
		{
			if (str[var->i])
				var->i++;
		}
		if ((*lex) && (*lex)->type == 's')
			(*lex) = (*lex)->next;
	}
}

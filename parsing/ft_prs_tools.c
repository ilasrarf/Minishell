/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prs_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:31:31 by aen-naas          #+#    #+#             */
/*   Updated: 2023/06/21 15:39:12 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_delemiter(t_lexer **lex)
{
	char *del;

	del = ft_strdup((*lex)->word);
	if ((*lex)->in_quotes)
		g_var->quot_checker = 1;
	(*lex) = (*lex)->next;
	while (*lex && ((*lex)->type == 'w' || (*lex)->type == 'v'))
	{
		if ((*lex)->in_quotes)
			g_var->quot_checker = 1;
		del = ft_strjoin(del, (*lex)->word);
		(*lex) = (*lex)->next;
	}
	return (del);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:09:07 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/03/23 23:54:22 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*str;
	char	*holder;
	t_lexer	*lex;
	t_parser *prs;

	prs = NULL;
	while (1)
	{
		str = readline("\e[91mMinishell$ \e[0m");
		if (!str)
			return (0);
		holder = str;
		if (ft_check_quotes(holder))
		{
			free(holder);
			exit(1);
		}
		ft_lexer(str, &lex);
		// while (lex)
		// {
		// 	printf("%s ", lex->word);
		// 	printf("%i ", lex->in_quotes);
		// 	printf("%c \n", lex->type);
		// 	lex = lex->next;
		// }
		free(holder);
		ft_parser(lex, &prs);
	}
}

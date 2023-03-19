/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:09:07 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/03/19 18:16:08 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*str;
	char	*holder;
	t_lexer	*lex;

	
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
		free(holder);
		lex = ft_parser(lex);
		while (lex)
		{
			printf("%s ", lex->word);
			printf("%c ", lex->type);
			printf("%i\n", lex->in_quotes);
			lex = lex->next;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:09:07 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/03/18 18:14:49 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*str;
	t_lexer	*lex;

	while (1)
	{
		str = readline("\e[91mMinishell$ \e[0m");
		if (!str)
			return (0);
		if (ft_check_quotes(str))
		{
			free(str);
			exit(1);
		}
		ft_lexer(str, &lex);
		while (lex)
		{
			printf("%s ", lex->word);
			printf("%c ", lex->type);
			printf("%i\n", lex->in_quotes);
			lex = lex->next;
		}
	}
}

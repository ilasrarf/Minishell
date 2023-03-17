/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:09:07 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/03/17 21:11:32 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*str;
	t_lexer *lex;

	while (1)
	{
		str = readline("\e[91mMinishell$ \e[0m");
		if (!str)
			return (0);
		ft_lexer(str, &lex);
		while (lex)
		{
			printf("%s\n", lex->word);
			lex = lex->next;
		}
	}
}

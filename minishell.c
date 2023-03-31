/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:09:07 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/03/31 20:16:51 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char		*str;
	char		*holder;
	t_lexer		*lex;
	t_parser	*prs;

	prs = NULL;
	(void)ac;
	(void)av;
	(void)env;
	while (1)
	{
		str = readline("\e[91mMinishell$ \e[0m");
		if (str && *str)
			add_history(str);
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
		// while(lex)
		// {
		// 	printf("word: %s\n",lex->word);
		// 	printf("type: %c\n", lex->type);
		// 	printf("in_q: %i\n", lex->in_quotes);
		// 	lex = lex->next;
		// 	printf("---------------\n");
		// }
		ft_parser(lex, &prs, env);
	}
}

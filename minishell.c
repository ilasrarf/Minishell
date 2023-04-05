/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:09:07 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/04/03 21:09:49 by ilasrarf         ###   ########.fr       */
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
		// ft_lstclear_lex(&lex);
		// while(lex)
		// {
		// 	printf("word: %s\n",lex->word);
		// 	printf("type: %c\n", lex->type);
		// 	printf("in_q: %i\n", lex->in_quotes);
		// 	lex = lex->next;
		// }
		ft_parser(lex, &prs, env);
		// printf("-------builtins part--------\n");
		ft_builtins(&prs);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:09:07 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/03/28 07:59:41 by aen-naas         ###   ########.fr       */
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
	// int fd = open ("/dev/urandom", O_RDONLY);
	// dup2(fd, 0);
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
		ft_parser(lex, &prs, env);
	}
}

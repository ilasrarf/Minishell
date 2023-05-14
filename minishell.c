/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:09:07 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/05/14 17:32:33 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_s;
//  t_var	*g_var;

void	handel(int signal)
{
	if (signal == SIGQUIT)
		return ;
	else if (signal == SIGINT)
	{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
	}
	else
		return ;
}

int	main(int ac, char **av, char **env)
{
	char		*str;
	char		**res;
	char		*holder;
	t_lexer		*lex;
	t_parser	*prs;
	t_env		*env_list;

	prs = NULL;
	exit_s = 0;
	(void)ac;
	(void)av;
	(void)res;
	(void)env_list;
	while (1)
	{
		signal(SIGINT, &handel);
		signal(SIGQUIT, &handel);
		if (isatty(STDIN_FILENO) == 0)
		{
			dup2(i, STDIN_FILENO);
			i = -1;
		}
		str = readline("\e[91mMinishell$ \e[0m");
		// rl_catch_signals = 0;
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
		if (prs)
		{
			if (env[0] != NULL)
				fill_env_list(env , &env_list);
			res = ft_reconver(&env_list);
			ft_excution(prs, env);
			// ft_status(exit_s);
			ft_lstclear(&prs);
		}
	}
}

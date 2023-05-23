/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:09:07 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/05/23 20:05:12 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*g_var;

void	handel(int signal)
{
	if (signal == SIGQUIT)
		return ;
	else if (signal == SIGINT)
	{
			g_var->exit_s = 1;
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
	}
	else
		return ;
}

t_var	*ft_lstnew_var(int x, int y,  char *name , char *value)
{
	t_var	*head;

	head = malloc(sizeof(t_var));
	head->exit_s = x;
	head->i = y;
	head->name = name;
	head->value = value;
	head->next = NULL;
	return head;
}

int	main(int ac, char **av, char **env)
{
	char		*str;
	char		**res;
	char		*holder;
	t_lexer		*lex;
	t_parser	*prs;
	t_env		*env_list;

	g_var = ft_lstnew_var(0, 0, NULL, NULL);
	(void)ac;
	(void)av;
	(void)res;
	(void)env;
	(void)env_list;
	g_var->PATH = "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.";
	prs = NULL;
	while (1)
	{
		signal(SIGINT, &handel);
		signal(SIGQUIT, &handel);
		// rl_catch_signals(0) = 0;
		if (isatty(STDIN_FILENO) == 0)
		{
			dup2(g_var->i, STDIN_FILENO);
			g_var->i = -1;
		}
		str = readline("\e[91mMinishell$ \e[0m");
		if (str && *str)
			add_history(str);
		if (!str)
		{
			printf("exit");
			return (0);
		}
		holder = str;
		if (ft_check_quotes(holder))
		{
			free(holder);
			g_var->exit_s = 2;
		}
		else
		{
			ft_lexer(str, &lex);
			// while(lex)
			// {
			// 	printf("word: %s\n",lex->word);
			// 	printf("type: %c\n", lex->type);
			// 	printf("in_q: %i\n", lex->in_quotes);
			// 	lex = lex->next;
			// 	printf("---------------\n");
			// }
			if (!*env)
				fill_empty_env(env , &env_list);
			else
				fill_env_list(env , &env_list, prs);
			res = ft_reconver(env_list);
			ft_free_env(&env_list);
			free(holder);
			ft_parser(lex, &prs, res);
			// if (prs)
			// {
			// 	ft_excution(prs, res);
			// 	ft_lstclear(&prs);
			// }
			ft_free(res);
			ft_lstclear_lex(&lex);
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:09:07 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/05/27 17:44:18 by ilasrarf         ###   ########.fr       */
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

void	ft_lex_pars(char *str, char **env, t_env **env_list)
{
	// static int	t = 0;
	char		**res;
	t_lexer		*lex;
	t_parser	*prs;

	prs = NULL;
	lex = NULL;
	ft_lexer(str, &lex);
	if (!*env)
		fill_empty_env(env, env_list);
	else if (!*env_list) 
		fill_env_list(env, env_list, prs);
	res = ft_reconver(*env_list);
	free(str);
	ft_parser(lex, &prs, res);
	if (prs)
	{
		ft_excution(prs, res, env_list);
		ft_lstclear(&prs);
	}
	// ft_free_env(&env_list);
	ft_free(res);
	ft_lstclear_lex(&lex);
}

int	ft_main(char *str, char **env, t_env **env_list)
{
	g_var->path = "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.";
	if (ft_check_quotes(str))
	{
		free(str);
		g_var->exit_s = 2;
	}
	else
		ft_lex_pars(str, env, env_list);
	return (0);
}

t_var	*ft_lstnew_var(int x, int y, char *name, char *value)
{
	t_var	*head;

	head = malloc(sizeof(t_var));
	head->exit_s = x;
	head->i = y;
	head->name = name;
	head->value = value;
	head->next = NULL;
	return (head);
}

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_env	*env_list;

	env_list = NULL;
	g_var = ft_lstnew_var(0, 0, NULL, NULL);
	(void)ac;
	(void)av;
	while (1)
	{
		signal(SIGINT, &handel);
		signal(SIGQUIT, &handel);
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
		
		ft_main(str, env, &env_list);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:09:07 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/06/02 21:25:13 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*g_var;

void	handel(int signal)
{
	static int i;

	if (signal == SIGQUIT)
		return ;
	else if (signal == SIGINT && waitpid(-1, NULL, WNOHANG))
	{
		if (g_var->in_hdc == 1)
			ft_herdoc_sig(&i);
		else
		{
			if (i != 1)
				write(1,"\n", 1);
			g_var->exit_s = 1;
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

void	ft_lex_pars(char *str, char **env, t_env **env_list)
{
	char		**res;
	t_lexer		*lex;
	t_lexer		*hold;
	static int in;
	t_parser	*prs;

	prs = NULL;
	lex = NULL;
	g_var->suspend = 1;
	g_var->overflow = 1;
	ft_lexer(str, &lex);
	hold  = lex;
	g_var->lex = hold;
	if (!*env && !*env_list && !in)
		fill_empty_env(env, env_list);
	else if (!*env_list && !in)
		fill_env_list(env, env_list, prs);
	in++;
	res = ft_reconver(*env_list);
	free(str);
	ft_parser(lex, &prs, res);
	if (prs && g_var->suspend)
		ft_excution(prs, res, env_list);
	if (prs)
		ft_lstclear(&prs);
	// ft_free_env(&env_list);
	ft_free(res);
	if (lex)
		ft_lstclear_lex(&lex);
}

int	ft_main(char *str, char **env, t_env **env_list)
{
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
	head->str = NULL;
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
	g_var->hi = 0;
	g_var->in_hdc = 0;
	g_var->str = NULL;
	while (1)
	{
		// rl_catch_signals = 0;
		signal(SIGINT, &handel);
		signal(SIGQUIT, &handel);
		if (isatty(STDIN_FILENO) == 0)
		{
			dup2(g_var->i, STDIN_FILENO);
			g_var->i = -1;
			// write(1, "\n", 1);
		}
		str = readline("\e[91mMinishell$ \e[0m");
		if (str && *str)
			add_history(str);
		if (!str)
		{
			printf("exit\n");
			return (g_var->exit_s);
		}
		ft_main(str, env, &env_list);
	}
}

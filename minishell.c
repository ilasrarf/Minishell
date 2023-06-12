/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:09:07 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/06/12 16:11:23 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*g_var;

void	handel(int signal)
{
	static int	i;

	if (signal == SIGQUIT)
		return ;
	else if (signal == SIGINT)
	{
		if (waitpid(-1, NULL, WNOHANG) == 0)
		{
			i = 0;
			return ;
		}
		if (g_var->in_hdc == 1)
		{
			ft_herdoc_sig(&i);
			g_var->in_hdc = 0;
			i++;
		}
		else
		{
			if (i == 0)
				write(1, "\n", 1);
			g_var->exit_s = 1;
			ft_norm_handel();
		}
	}
}

void	ft_lex_pars(char *str, char **env, t_env **env_list)
{
	char		**res;
	t_lexer		*lex;
	t_lexer		*hold;
	static int	in;
	t_parser	*prs;

	prs = NULL;
	lex = NULL;
	ft_lexer(str, &lex);
	hold = lex;
	g_var->lex = hold;
	fill_env(env_list, prs, env, in);
	in++;
	res = ft_reconver(*env_list);
	free(str);
	ft_parser(lex, &prs, res);
	free(g_var->fd);
	if (prs && g_var->suspend)
		ft_excution(prs, res, env_list);
	if (prs)
		ft_lstclear(&prs);
	ft_free(res);
	if (lex)
		ft_lstclear_lex(&lex);
}

int	ft_main(char *str, char **env, t_env **env_list)
{
	if (ft_check_quotes(str))
	{
		ft_putstr_fd("inclosed quote\n", 2);
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
	head->hi = 0;
	head->fd = 0;
	head->size = 0;
	head->index = 0;
	head->in_hdc = 0;
	head->str = NULL;
	head->relock = NULL;
	head->next = NULL;
	head->suspend = 1;
	head->overflow = 1;
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
	rl_catch_signals = 0;
	while (1)
	{
		signal(SIGINT, &handel);
		signal(SIGQUIT, &handel);
		if (ttyname(STDIN_FILENO) == 0)
		{
			dup2(g_var->i, STDIN_FILENO);
			write(1, "\n", 1);
		}
		str = readline("Minishell$");
		if (str && *str)
			add_history(str);
		if (!str)
			return (ft_exit_main());
		ft_main(str, env, &env_list);
	}
}

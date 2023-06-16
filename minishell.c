/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:09:07 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/06/16 20:10:15 by ilasrarf         ###   ########.fr       */
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
		if (waitpid(-1, NULL, WNOHANG) == 0)
			return ;
		if (g_var->in_hdc == 1)
		{
			ft_herdoc_sig();
			g_var->in_hdc = 0;
		}
		else
		{
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
	g_var->suspend = 1;
	ft_lexer(str, &lex);
	hold = lex;
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

t_var	*ft_lstnew_var(void)
{
	t_var	*head;

	head = malloc(sizeof(t_var));
	head->exit_s = 0;
	head->i = 0;
	head->str = NULL;
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
	g_var = ft_lstnew_var();
	(void)ac;
	(void)av;
	while (1)
	{
		signal(SIGINT, &handel);
		signal(SIGQUIT, &handel);
		rl_catch_signals = 0;
		if (isatty(STDIN_FILENO) == 0)
		{
			dup2(g_var->i, STDIN_FILENO);
			close(g_var->i);
		}
		str = readline("Minishell$ ");
		if (str && *str)
			add_history(str);
		if (!str)
			return (ft_exit_main());
		ft_main(str, env, &env_list);
	}
}

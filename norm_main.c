/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 22:13:26 by aen-naas          #+#    #+#             */
/*   Updated: 2023/06/17 15:52:25 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_status_for_path(t_env **env)
{
	t_env	*tmp;

	tmp = (*env);
	while ((*env))
	{
		if (!ft_strcmp("PATH", (*env)->name))
			(*env)->st = 3;
		(*env) = (*env)->next;
	}
	(*env) = tmp;
}

void	fill_env(t_env **env_list, t_parser *prs, char **env, int in)
{
	if (!*env && !*env_list && !in)
	{
		fill_empty_env(env, env_list);
		set_status_for_path(env_list);
	}
	else if (!*env_list && !in)
		fill_env_list(env, env_list, prs);
}

int	ft_exit_main(void)
{
	int	i;

	i = g_var->exit_s;
	printf("exit\n");
	free(g_var);
	return (i);
}

int	ft_chrwithe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			return (1);
		i++;
	}
	return (0);
}

void	ft_norm_join_var_il(char **str, char *str2, int i, int j)
{
	if (str2 && ft_chrwithe(str2) && !j)
	{
		if (g_var->relock)
			ft_free(g_var->relock);
		g_var->relock = ft_realloc(str2, str);
		free(str2);
	}
	else
		str[i] = str2;
}

char *ft_join_args(t_lexer **lex, char **str, char **env, int i)
{
	char *str1;

	
	if ((*lex)->type == 'v')
	{
		str1 = ft_hendel_var((*lex)->word, env);
		str[i] = ft_strjoin(str[i], str1);
		free(str1);
	}
	else
		str[i] = ft_strjoin(str[i], (*lex)->word);
	(*lex) = (*lex)->next;
	return str[i];
}

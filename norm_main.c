/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 22:13:26 by aen-naas          #+#    #+#             */
/*   Updated: 2023/06/04 21:59:14 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_status_for_path(t_env **env)
{
	t_env *tmp;

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
	printf("exit\n");
	free(g_var);
	return (g_var->exit_s);
}

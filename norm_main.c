/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 22:13:26 by aen-naas          #+#    #+#             */
/*   Updated: 2023/06/12 11:47:23 by aen-naas         ###   ########.fr       */
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

int ft_chrwithe(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			return (1);
		i++;
	}
	return (0);
}


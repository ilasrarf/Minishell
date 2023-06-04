/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 22:13:26 by aen-naas          #+#    #+#             */
/*   Updated: 2023/06/04 21:56:09 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_env(t_env **env_list, t_parser *prs ,char **env, int in)
{
	if (!*env && !*env_list && !in)
		fill_empty_env(env, env_list);
	else if (!*env_list && !in)
		fill_env_list(env, env_list, prs);
}

int	ft_exit_main()
{
	printf("exit\n");
	free(g_var);
	return (g_var->exit_s);
}
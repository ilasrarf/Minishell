/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 22:13:26 by aen-naas          #+#    #+#             */
/*   Updated: 2023/06/02 22:18:15 by aen-naas         ###   ########.fr       */
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
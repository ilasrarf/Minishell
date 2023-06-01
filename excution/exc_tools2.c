/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:49:58 by aen-naas          #+#    #+#             */
/*   Updated: 2023/06/01 21:41:42 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_excve(t_parser *pars, char **env, t_env **env_list)
{
	char	*str;
	int		i;

	signal(SIGINT, SIG_DFL);
	i = ft_builtins(&pars, env_list);
	if (pars->args[0] && !i)
	{
		str = ft_check_path(pars->args[0], env);
		if (execve(str, pars->args, env) == -1)
			ft_print_error(pars->args[0]);
	}
	exit(0);
}

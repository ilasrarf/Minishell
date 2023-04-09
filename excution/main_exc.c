/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:01:38 by aen-naas          #+#    #+#             */
/*   Updated: 2023/04/09 21:25:06 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exc(t_parser *pars, char **env)
{
	int	id;
	int fd;
	char *str;

	id = fork();
	if (id == 0)
	{
		if (pars->out_red)
			fd = ft_red_out(pars, env);
		str = ft_strjoin(ft_strdup("/bin/"), pars->args[0]);
		if (execve(str, &(pars->args[0]), env) == -1)
			exit(0);
	}
	wait(NULL);
}

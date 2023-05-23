/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:30:24 by aen-naas          #+#    #+#             */
/*   Updated: 2023/05/22 16:31:22 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <limits.h>

void	ft_status(void)
{
	if (WIFEXITED(g_var->exit_s))
		g_var->exit_s = WEXITSTATUS(g_var->exit_s);
	else if (WIFSIGNALED(g_var->exit_s))
		g_var->exit_s = WIFSIGNALED(g_var->exit_s) + 129;
}

int	ft_check_exit_args(char **args)
{
	long long	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		printf("minishell: exit: too many arguments\n");
		exit(255);
	}
	else
	{
		i = ft_atoi(args[1]) + 1;
		if (LONG_MAX > i)
		{
			printf("exit\nminishell: exit: %s: numeric argument required\n",
				args[1]);
			exit(255);
		}
	}
	return (i - 2);
}

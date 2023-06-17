/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:30:24 by aen-naas          #+#    #+#             */
/*   Updated: 2023/06/17 12:32:36 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <limits.h>

void	ft_status(void)
{
	if (WIFEXITED(g_var->exit_s))
		g_var->exit_s = WEXITSTATUS(g_var->exit_s);
	else if (WIFSIGNALED(g_var->exit_s))
		g_var->exit_s = WTERMSIG(g_var->exit_s) + 128;
}

int	ft_check_exit_args(char **args)
{
	long	i;

	i = 0;
	if (args[1] == NULL)
		return (0);
	while (args[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		g_var->exit_s = 1;
		return (1);
	}
	else
	{
		i = ft_atoi_exit(args[1]);
		if (g_var->overflow == -1)
		{
			ft_putstr_fd("exit\nminishell: exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
	}
	return (0);
}

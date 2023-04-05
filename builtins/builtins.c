/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 02:48:29 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/04/03 20:51:13 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_handel_n(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_handel_echo(t_parser **prs)
{
	int	f;
	int	i;

	i = 1;
	f = 0;
	while ((*prs)->args[i])
	{
		if (!ft_strncmp((*prs)->args[i], "-n", 2) && f == 0)
		{
			f = ft_handel_n((*prs)->args[i]);
			if (f == 0)
			{
				ft_putstr_fd((*prs)->args[i], (*prs)->out_red);
				write((*prs)->out_red, " ", 1);
			}
		}
		else
		{
			ft_putstr_fd((*prs)->args[i], (*prs)->out_red);
			write((*prs)->out_red, " ", 1);
		}
		i++;
	}
	if (f == 0)
		write((*prs)->out_red, "\n", 1);
}

void	ft_builtins(t_parser **prs)
{
	if (!ft_strcmp((*prs)->args[0], "echo") || !ft_strcmp((*prs)->args[0],
			"ECHO"))
		ft_handel_echo(prs);
	else if (!ft_strcmp((*prs)->args[0], "cd") || !ft_strcmp((*prs)->args[0],
			"CD"))
		ft_handel_cd(prs);
}

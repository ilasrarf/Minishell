/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 02:48:29 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/05/26 15:34:37 by ilasrarf         ###   ########.fr       */
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
		if (!ft_strncmp((*prs)->args[i], "-", 1))
		{
			f = ft_handel_n((*prs)->args[i]);
			if (f == 0)
			{
				ft_putstr_fd((*prs)->args[i], 1);
				if ((*prs)->args[i + 1])
					write(1, " ", 1);
			}
		}
		else
		{
			ft_putstr_fd((*prs)->args[i], 1);
			if ((*prs)->args[i + 1])
				write(1, " ", 1);
		}
		i++;
	}
	if (f == 0)
		write(1, "\n", 1);
}

int	ft_builtins(t_parser **prs, t_env **env_list)
{
	if (!ft_strcmp((*prs)->args[0], "exit"))
			exit(0);
	if (!ft_strcmp((*prs)->args[0], "echo") || !ft_strcmp((*prs)->args[0], "ECHO"))
	{
		ft_handel_echo(prs);
		return (1);
	}
	else if (!ft_strcmp((*prs)->args[0], "cd") || !ft_strcmp((*prs)->args[0], "CD"))
	{
		ft_handel_cd(prs, env_list);
		return (1);
	}
	else if (!ft_strcmp((*prs)->args[0], "pwd") || !ft_strcmp((*prs)->args[0], "PWD"))
	{
		ft_handel_pwd(env_list);
		return (1);
	}
	else if (!ft_strcmp((*prs)->args[0], "env") || !ft_strcmp((*prs)->args[0], "ENV"))
	{
		ft_handel_env(env_list);
		return (1);
	}
	else if (!ft_strcmp((*prs)->args[0], "export") || !ft_strcmp((*prs)->args[0], "EXPORT"))
	{
		ft_handel_export(prs, env_list);
		return (1);
	}
	// else if (!ft_strcmp((*prs)->args[0], "unset") || !ft_strcmp((*prs)->args[0],
	// 		"UNSET"))
	// 	ft_handel_unset(prs, env_list);
	return (0);
}                                           

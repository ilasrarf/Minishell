/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 02:48:29 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/06/04 22:00:00 by ilasrarf         ###   ########.fr       */
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
	int	j;

	i = 1;
	f = 0;
	j = 0;
	if (!(*prs)->args[i])
		return ;
	while ((*prs)->args[i])
	{
		ft_norm_echo(prs, i, &j, f);
		i++;
	}
	if ((*prs)->args[1][1])
	{
		if (!ft_handel_n((*prs)->args[1]))
			write((*prs)->out_red, "\n", 1);
	}
	else
		write((*prs)->out_red, "\n", 1);
}

int	ft_norm_buil1(t_parser **prs, t_env **env_list)
{
	if (!ft_strcmp((*prs)->args[0], "echo") || !ft_strcmp((*prs)->args[0],
			"ECHO"))
	{
		g_var->exit_s = 0;
		ft_handel_echo(prs);
		return (1);
	}
	else if (!ft_strcmp((*prs)->args[0], "cd") || !ft_strcmp((*prs)->args[0],
			"CD"))
	{
		g_var->exit_s = 0;
		ft_handel_cd(prs, env_list);
		return (1);
	}
	else if (!ft_strcmp((*prs)->args[0], "pwd") || !ft_strcmp((*prs)->args[0],
			"PWD"))
	{
		g_var->exit_s = 0;
		ft_handel_pwd(env_list);
		return (1);
	}
	return (0);
}

int	ft_norm_buil2(t_parser **prs, t_env **env_list)
{
	if (!ft_strcmp((*prs)->args[0], "env") || !ft_strcmp((*prs)->args[0],
			"ENV"))
	{
		g_var->exit_s = 0;
		ft_handel_env(env_list);
		return (1);
	}
	else if (!ft_strcmp((*prs)->args[0], "export")
		|| !ft_strcmp((*prs)->args[0], "EXPORT"))
	{
		g_var->exit_s = 0;
		ft_handel_export(prs, env_list);
		return (1);
	}
	else if (!ft_strcmp((*prs)->args[0], "unset") || !ft_strcmp((*prs)->args[0],
			"UNSET"))
	{
		g_var->exit_s = 0;
		ft_handel_unset(prs, env_list);
		return (1);
	}
	return (0);
}

int	ft_builtins(t_parser **prs, t_env **env_list)
{
	if (!ft_strcmp((*prs)->args[0], "exit"))
	{
		if (!ft_check_exit_args((*prs)->args))
		{
			if (g_var->exc)
				write(1, "exit\n", 5);
			if ((*prs)->args[1])
				exit(ft_atoi_exit((*prs)->args[1]));
		}
		exit(0);
	}
	else if (ft_norm_buil1(prs, env_list) == 0 && ft_norm_buil2(prs,
			env_list) == 0)
		return (0);
	else
		return (1);
}

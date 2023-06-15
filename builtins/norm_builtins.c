/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:38:14 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/06/15 14:33:41 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_norm_echo(t_parser **prs, int i, int *j, int f)
{
	if (!ft_strncmp((*prs)->args[i], "-", 1) && *j == 0)
	{
		f = ft_handel_n((*prs)->args[i]);
		if (f == 0)
		{
			*j = 1;
			ft_putstr_fd((*prs)->args[i], (*prs)->out_red);
			if ((*prs)->args[i + 1])
				write((*prs)->out_red, " ", 1);
		}
	}
	else
	{
		*j = 1;
		ft_putstr_fd((*prs)->args[i], (*prs)->out_red);
		if ((*prs)->args[i + 1])
			write((*prs)->out_red, " ", 1);
	}
}

void	ft_norm_export(char *str, int i, t_env **env)
{
	if (str[i] == '+')
	{
		if ((*env)->value)
			(*env)->value = ft_strjoin((*env)->value, str + i + 2);
		else
			(*env)->value = ft_strjoin(ft_strdup(""), str + i + 2);
		(*env)->st = 1;
	}
	else
	{
		free((*env)->value);
		(*env)->value = ft_strdup(str + i + 1);
		(*env)->st = 1;
	}
}

void	ft_norm_unset(t_env **env, t_parser **prs, t_bvar **var, int i)
{
	if ((*env) && !ft_strcmp((*env)->name, (*prs)->args[i]))
	{
		(*var)->tmp = (*env)->next;
		ft_lstdelone_env((*env));
		return ;
	}
	while ((*env))
	{
		if ((*env)->next && !ft_strcmp((*env)->next->name, (*prs)->args[i]))
		{
			(*var)->h1 = (*env);
			if ((*var)->h1->next->next)
				(*var)->h2 = (*var)->h1->next->next;
			else
				(*var)->h2 = NULL;
			ft_lstdelone_env((*env)->next);
			(*var)->h1->next = (*var)->h2;
		}
		(*env) = (*env)->next;
	}
}

char	*ft_get_pwd(t_env **env)
{
	t_env	*tmp;

	tmp = (*env);
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "PWD"))
		{
			if (tmp->value)
				return (ft_strdup(tmp->value));
			else
				return (ft_strdup(""));
		}
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}
int ft_check_path_if_exist(char *path)
{
	int i;
	int j;
	char *str;

	str = "/usr/bin";
	i = 0;
	while (path[i])
	{
		j = 0;
		while (str[j])
		{
			if (str[j] != path[i])
				break ;
			i++;
			j++;
		}
		i++;
	}
	if (str[i] == '\0')
		return (1);
	return (0);
}

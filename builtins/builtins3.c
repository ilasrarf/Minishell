/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:54:07 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/06/16 20:40:10 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_prs_exp(char *str)
{
	int	i;

	i = 0;
	if (str && !str[0])
		return (2);
	if (!(str[i] >= 'A' && str[i] <= 'Z') && !(str[i] >= 'a' && str[i] <= 'z')
		&& str[i] != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] != '=')
			return (0);
		else if (!(str[i] >= 'A' && str[i] <= 'Z') && !(str[i] >= 'a'
				&& str[i] <= 'z') && str[i] != '_' && !(str[i] >= '0'
				&& str[i] <= '9') && str[i] != '+')
			return (0);
		i++;
	}
	return (1);
}

void	ft_write_error(int fd, char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(fd, "minishell: export: `", 20);
	write(fd, str, i);
	write(fd, "': not a valid identifier\n", 26);
}

void	ft_print_exp(t_env **env)
{
	t_env	*tmp1;

	tmp1 = *env;
	while ((*env))
	{
		if ((*env)->st != 3)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd((*env)->name, 1);
			if ((*env)->value)
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd((*env)->value, 1);
				ft_putstr_fd("\"", 1);
			}
		}
		ft_putstr_fd("\n", 1);
		(*env) = (*env)->next;
	}
	*env = tmp1;
}

void	ft_add_var(t_parser **prs, t_env **env, int i, int *j)
{
	*j = 1;
	if (!is_exist((*prs)->args[i], *env))
		add_new_to_env((*prs)->args[i], env);
	else
		add_old_to_env((*prs)->args[i], env);
}

void	ft_handel_export(t_parser **prs, t_env **env)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	printf("----> %s\n", (*prs)->args[1]);
	while ((*prs)->args[i])
	{
		if (ft_prs_exp((*prs)->args[i]) == 0)
		{
			j++;
			g_var->exit_s = 1;
			ft_write_error(2, (*prs)->args[i]);
		}
		else if (ft_prs_exp((*prs)->args[i]) != 2)
		{
			if ((*prs)->args[i][0])
				ft_add_var(prs, env, i, &j);
		}
		i++;
	}
	if (j == 0)
		ft_print_exp(env);
}

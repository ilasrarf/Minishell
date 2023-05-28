/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:54:07 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/05/28 20:48:05 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_prs_exp(char *str)
{
	int	i;

	i = 0;
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
		printf("declare -x %s=", (*env)->name);
		printf("\"%s\"\n", (*env)->value);
		(*env) = (*env)->next;
	}
	*env = tmp1;
}

void	ft_handel_export(t_parser **prs, t_env **env)
{
	int	i;

	i = 1;
	if (!(*prs)->args[1])
	{
		ft_print_exp(env);
		return ;
	}
	while ((*prs)->args[i])
	{
		if (ft_prs_exp((*prs)->args[i]) == 0)
			ft_write_error(2, (*prs)->args[i]);
		else
		{
			if (!is_exist((*prs)->args[i], *env))
				add_new_to_env((*prs)->args[i], env);
			else
				add_old_to_env((*prs)->args[i], env);
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:33:10 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/06/16 19:42:26 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_prs_exp_unset(char *str)
{
	int	i;

	i = 0;
	if (!(str[i] >= 'A' && str[i] <= 'Z') && !(str[i] >= 'a' && str[i] <= 'z')
		&& str[i] != '_')
		return (0);
	while (str[i])
	{
		if (str[i] == '+' || str[i] == '=')
			return (0);
		else if (!(str[i] >= 'A' && str[i] <= 'Z') && !(str[i] >= 'a'
				&& str[i] <= 'z') && str[i] != '_' && !(str[i] >= '0'
				&& str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	check_path_built(char *str, char *substr)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i + j] == substr[j])
		{
			if (substr[j + 1] == '\0')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

char	*get_value_from_env(t_env **env, char *name)
{
	t_env	*tmp;

	tmp = (*env);
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_check_num(char *str)
{
	int	i;

	i = 0;
	if (!ft_strlen(str))
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

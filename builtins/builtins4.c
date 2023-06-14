/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:24:53 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/06/13 22:53:19 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_new_to_env(char *str, t_env **env)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (str[i] && str[i] != '+' && str[i] != '=')
		i++;
	if (str[i] == '+')
		ft_lstadd_back_env(env, ft_lstnew_env(ft_substr(str, 0, i),
				ft_strdup(str + i + 2)));
	else if (str[i] != '=')
		ft_lstadd_back_env(env, ft_lstnew_env(ft_strdup(str), NULL));
	else
		ft_lstadd_back_env(env, ft_lstnew_env(ft_substr(str, 0, i),
				ft_strdup(str + i + 1)));
}

void	add_old_to_env(char *str, t_env **env)
{
	int		i;
	t_env	*tmp;

	tmp = *env;
	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	if (!ft_strchr(str, '='))
		return ;
	while ((*env))
	{
		if (!ft_strncmp((*env)->name, str, i))
			ft_norm_export(str, i, env);
		(*env) = (*env)->next;
	}
	(*env) = tmp;
}

int	is_exist(char *str, t_env *env_list)
{
	int		i;
	char	*str1;

	i = 0;
	while (*str && str[i] && str[i] != '+' && str[i] != '=')
		i++;
	str1 = ft_substr(str, 0, i);
	while (env_list)
	{
		if (!ft_strcmp(env_list->name, str1))
		{
			free(str1);
			return (1);
		}
		env_list = env_list->next;
	}
	free(str1);
	return (0);
}

int	is_exist_env(char *str, t_env *env_list)
{
	int		i;
	char	*str1;

	i = 0;
	while (*str && str[i] && str[i] != '+' && str[i] != '=')
		i++;
	str1 = ft_substr(str, 0, i);
	while (env_list)
	{
		if (!ft_strcmp(env_list->name, str1))
		{
			free(str1);
			return (1);
		}
		env_list = env_list->next;
	}
	free(str1);
	return (0);
}

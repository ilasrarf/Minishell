/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_envlist.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:08:38 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/05/09 15:42:10 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char	**ft_reconver(t_env **env)
{
	int i;
	char **res;
	t_env *tmp;

	
	i = 0;
	tmp = *env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	res = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (*env)
	{
		res[i] = ft_strjoin(ft_strjoin_char((*env)->name, '='), (*env)->value);
		i++;
		(*env) = (*env)->next;
	}
	res[i] = NULL;
	return res;
}

int	ft_cnt_name(char *str)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (str[i] != '=')
	{
		cnt++;
		i++;
	}
	return (cnt);
}

int	ft_cnt_val(char *str)
{
	int	i;
	int	cnt;
	int	h;
	
	cnt = 0;
	h = 0;
	i = 0;
	while (str[i])
	{
		if (h == 1)
			cnt++;
		if (str[i] == '=')
			h = 1;
		i++;
	}
	return (cnt);
}

void	fill_env_list(char **env, t_env **env_list)
{
	int	i;
	int	cnt1;

	i = 1;
	cnt1 = ft_cnt_name(env[0]);
	*env_list = ft_lstnew_env(ft_substr(env[0], 0, cnt1)
		, ft_substr(env[0], cnt1 + 1, ft_cnt_val(env[0])));
	while (env[i])
	{
		cnt1 = ft_cnt_name(env[i]);
		ft_lstadd_back_env(env_list, ft_lstnew_env(ft_substr(env[i], 0, cnt1)
			, ft_substr(env[i], cnt1 + 1, ft_cnt_val(env[i]))));
		i++;
	}
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_envlist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:08:38 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/05/06 16:33:03 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

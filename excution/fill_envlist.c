/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_envlist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:31:42 by aen-naas          #+#    #+#             */
/*   Updated: 2023/05/22 16:32:41 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_reconver(t_env *env)
{
	int		i;
	char	**res;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	res = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (env)
	{
		res[i] = ft_strjoin(ft_strjoin_char(ft_strdup((env)->name), '='),
				(env)->value);
		i++;
		(env) = (env)->next;
	}
	return (res);
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

void	fill_env_list(char **env, t_env **env_list, t_parser *pars)
{
	int	i;
	int	j;
	int	cnt1;

	i = 1;
	j = 0;
	cnt1 = ft_cnt_name(env[0]);
	*env_list = ft_lstnew_env(ft_substr(env[0], 0, cnt1), ft_substr(env[0], cnt1
				+ 1, ft_cnt_val(env[0])));
	while (env[i])
	{
		cnt1 = ft_cnt_name(env[i]);
		if (!ft_strncmp("SHLVL=", env[i], cnt1 + 1))
			ft_extra_handel(env_list, pars, env[i]);
		else if (pars && !env[i + 1])
			ft_extra_handel(env_list, pars, env[i]);
		else
			ft_lstadd_back_env(env_list, ft_lstnew_env(ft_substr(env[i], 0,
						cnt1), ft_substr(env[i], cnt1 + 1,
						ft_cnt_val(env[i]))));
		i++;
	}
}

void	fill_empty_env(char **env, t_env **env_list)
{
	char	pwd[1024];

	(void)env;
	getcwd(pwd, sizeof(pwd));
	*env_list = ft_lstnew_env(ft_strdup("PWD"), ft_strdup(pwd));
	ft_lstadd_back_env(env_list, ft_lstnew_env(ft_strdup("SHLVL"), ft_itoa(1)));
	ft_lstadd_back_env(env_list, ft_lstnew_env(ft_strdup("_"),
			ft_strdup("/usr/bin/env")));
}

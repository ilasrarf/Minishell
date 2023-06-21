/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 22:13:26 by aen-naas          #+#    #+#             */
/*   Updated: 2023/06/21 18:20:10 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_status_for_path(t_env **env)
{
	t_env	*tmp;

	tmp = (*env);
	while ((*env))
	{
		if (!ft_strcmp("PATH", (*env)->name))
			(*env)->st = 3;
		(*env) = (*env)->next;
	}
	(*env) = tmp;
}

void	fill_env(t_env **env_list, t_parser *prs, char **env, int in)
{
	if (!*env && !*env_list && !in)
	{
		fill_empty_env(env, env_list);
		set_status_for_path(env_list);
	}
	else if (!*env_list && !in)
		fill_env_list(env, env_list, prs);
}

int	ft_exit_main(void)
{
	int	i;

	i = g_var->exit_s;
	printf("exit\n");
	free(g_var);
	return (i);
}

int	ft_chrwithe(char *str1)
{
	int	i;
	int	cnt;
	char *str;
	cnt = 0;
	i = 0;
	
	str = ft_my_strtrim_w(str1);
	while (str[i])
	{
		if ((str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			&& !(str[i + 1] == ' ' || (str[i + 1] >= 9 && str[i + 1] <= 13)))
			cnt++;
		i++;
	}
	free(str);
	if (i == 0)
		return (0);
	if (!cnt)
		return (0);
	return (1);
}

void	ft_norm_join_var_il(char **str, char *str2, int i, int j)
{
	if (str2 && ft_chrwithe(str2) && !j)
	{
		if (g_var->relock)
			ft_free(g_var->relock);
		g_var->relock = ft_realloc(str2, str);
		free(str2);
	}
	else
		str[i] = str2;
}

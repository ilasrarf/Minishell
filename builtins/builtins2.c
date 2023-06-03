/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 20:47:58 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/06/03 22:09:21 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_chang_ocwd(t_env **env, char *old)
{
	t_env	*tmp;
	int		j;

	j = 0;
	tmp = (*env);
	while ((*env))
	{
		if (ft_strcmp((*env)->name, "OLDPWD") == 0)
		{
			j++;
			free((*env)->value);
			(*env)->value = ft_strdup(old);
		}
		else if ((*env)->next == NULL && j == 0)
			ft_lstadd_back_env(env, ft_lstnew_env(ft_strdup("OLDPWD"),
					ft_strdup(old)));
		(*env) = (*env)->next;
	}
	(*env) = tmp;
}

void	ft_chang_cwd(t_env **env, char *cur)
{
	t_env	*tmp;

	tmp = (*env);
	while ((*env))
	{
		if (ft_strcmp((*env)->name, "PWD") == 0)
		{
			free((*env)->value);
			(*env)->value = ft_strdup(cur);
		}
		(*env) = (*env)->next;
	}
	(*env) = tmp;
}

char	*get_home(t_env **env)
{
	t_env	*tmp;
	t_env	*hold;
	int		cnt;

	cnt = 0;
	tmp = (*env);
	while ((*env))
	{
		if (!ft_strcmp("HOME", (*env)->name))
		{
			if ((*env)->name[4] == '\0')
			{
				cnt = 1;
				hold = (*env);
			}
		}
		(*env) = (*env)->next;
	}
	(*env) = tmp;
	if (cnt == 0)
		return (write(2, "minishell: cd: HOME not set\n", 28), g_var->hi = 1,
			NULL);
	else
		return (hold->value);
	return ((*env)->value);
}

void	ft_handel_cd(t_parser **prs, t_env **env)
{
	int		i;
	char	cur[1024];
	char	*old;

	old = ft_get_pwd(env);
	ft_chang_ocwd(env, old);
	if ((*prs)->args[1])
		i = chdir((*prs)->args[1]);
	else
		i = chdir(get_home(env));
	if (g_var->hi == 1)
		g_var->exit_s = 1;
	if (i == -1 && g_var->hi == 0)
	{
		g_var->exit_s = 1;
		printf("cd: %s: No such file or directory\n", (*prs)->args[1]);
		return ;
	}
	getcwd(cur, sizeof(cur));
	ft_chang_cwd(env, cur);
}

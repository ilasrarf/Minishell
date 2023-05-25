/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 20:47:58 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/05/20 14:50:18 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int hi = 0;

void	ft_chang_ocwd(t_env **env, char *old)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = (*env);	
	while ((*env))
	{
		if (ft_strncmp((*env)->name, "OLDPWD", 6) == 0)
		{
			free((*env)->value);
			(*env)->value = ft_strdup(old);
		}
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
		if (ft_strncmp((*env)->name, "PWD", 3) == 0)
		{
			free((*env)->value);
			(*env)->value = ft_strdup(cur);
		}
		(*env) = (*env)->next;
	}
	(*env) = tmp;
}
char *get_home(t_env **env)
{
	t_env	*tmp;
	t_env	*hold;
	int		cnt;

	cnt = 0;
	tmp = (*env);
	while ((*env))
	{
		if (!ft_strncmp("HOME",(*env)->name,  4))
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
		return (write(1, "minishell: cd: HOME not set\n", 28), hi = 1, NULL);
	else
		return (hold->value);
	return ((*env)->value);
}
void    ft_handel_cd(t_parser **prs,  t_env **env)
{
	int		i;
	char	cur[1024];
	char	old[1024];
	
	getcwd(old, sizeof(old));
	ft_chang_ocwd(env, old);
	if ((*prs)->args[1])
		i = chdir((*prs)->args[1]);
	else
		i = chdir(get_home(env));
	if(i == -1 && hi == 0)
	{
		printf("cd: %s: No such file or directory\n", (*prs)->args[1]);
		return;
	}
	getcwd(cur, sizeof(cur));
	ft_chang_cwd(env, cur);
}

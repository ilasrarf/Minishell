/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:39:09 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/06/15 14:32:21 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_handel_env(t_env **env)
{
	t_env	*tmp1;

	tmp1 = *env;
	if (is_exist("PATH", *env) == 0
		|| check_path_built(get_value_from_env(env, "PATH"), "/usr/bin") == 0)
	{
		ft_putstr_fd("Minishell: env: No such file or directory\n", 2);
		return ;
	}
	while ((*env))
	{
		if ((*env)->st == 1)
		{
			ft_putstr_fd((*env)->name, 1);
			write(1, "=", 1);
			ft_putstr_fd((*env)->value, 1);
			write(1, "\n", 1);
		}
		(*env) = (*env)->next;
	}
	*env = tmp1;
}

void	ft_handel_pwd(t_env **env)
{
	t_env	*tmp1;
	char	cur[1024];

	tmp1 = *env;
	getcwd(cur, sizeof(cur));
	if (cur[0])
	{
		ft_putstr_fd(cur, 1);
		write(1, "\n", 1);
	}
	else
	{
		while ((*env))
		{
			if (ft_strncmp((*env)->name, "PWD", 3) == 0)
			{
				ft_putstr_fd((*env)->value, 1);
				write(1, "\n", 1);
				*env = tmp1;
			}
			(*env) = (*env)->next;
		}
		*env = tmp1;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:56:14 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/06/15 14:32:41 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_write_error_unset(int fd, char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(fd, "minishell: unset: `", 20);
	write(fd, str, i);
	write(fd, "': not a valid identifier\n", 26);
}

void	ft_handel_unset(t_parser **prs, t_env **env)
{
	t_bvar	*var;
	int		i;

	i = 1;
	var = malloc(sizeof(t_bvar));
	var->h1 = NULL;
	var->h2 = NULL;
	if (!(*prs)->args[1])
		return ;
	var->tmp = (*env);
	while ((*prs)->args[i])
	{
		if (ft_prs_exp_unset((*prs)->args[i]) == 0)
		{
			g_var->exit_s = 1;
			ft_write_error_unset(2, (*prs)->args[i]);
		}
		ft_norm_unset(env, prs, &var, i);
		(*env) = var->tmp;
		i++;
	}
	(*env) = var->tmp;
	free(var);
}

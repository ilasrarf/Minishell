/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:54:07 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/05/25 23:35:31 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_write_error(int fd, char *str)
{
	int i = 0;

	while (str[i])
		i++;
	write(fd, "minishell: export: `", 20);
	write(fd, str, i);
	write(fd, "': not a valid identifier\n", 26);
	
}

void	ft_print_exp(t_env **env)
{
	t_env *tmp1;

	tmp1 = *env;
	while ((*env))
	{
		printf("declare -x %s=", (*env)->name);
		printf("\"%s\"\n", (*env)->value);
		(*env) = (*env)->next;
	}
	*env = tmp1;
}

void    ft_handel_export(t_parser **prs, t_env **env)
{
	// int i = 0;
	
	printf("----%s----" ,(*prs)->args[0]);
	if (!(*prs)->args[1])
	{
		ft_print_exp(env);
		return;
	}
	// while((*prs)->args[i])
	// {
	// 	if (ft_prs_exp((*prs)->args[i]) == 0)
	// 		ft_write_error(2, (*prs)->args[i]);
		
	// 	i++;
	// }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:47:12 by aen-naas          #+#    #+#             */
/*   Updated: 2023/06/21 21:52:47 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_free_env(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		free((*env)->name);
		free((*env)->value);
		tmp = (*env)->next;
		free(*env);
		(*env) = (*env)->next;
	}
}

void	ft_free_char(char **str)
{
	free(*str);
	*str = NULL;
}

void	ft_free_and_null(char **del)
{
	free(*del);
	*del = NULL;
}

void	ft_asigen_global(void)
{
	g_var->suspend = 1;
	g_var->fd_hd = 0;
	g_var->quot_checker = 0;
}

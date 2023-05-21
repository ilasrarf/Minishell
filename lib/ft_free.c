/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:47:12 by aen-naas          #+#    #+#             */
/*   Updated: 2023/05/18 20:36:57 by aen-naas         ###   ########.fr       */
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
	t_env *tmp = *env;
	while ((*env))
	{
		// free((*env)->name);
		free((*env)->value);
		(*env) = (*env)->next;
	}
	free(tmp);
	*env = NULL;
}
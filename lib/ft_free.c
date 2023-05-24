/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:47:12 by aen-naas          #+#    #+#             */
/*   Updated: 2023/05/24 15:43:46 by aen-naas         ###   ########.fr       */
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

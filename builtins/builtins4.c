/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:24:53 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/05/26 20:30:03 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void    add_to_env(char *str, t_env **env)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	while (str[i] && str[i] != '=')
		i++;
	if (str[i]== '=')
	{
		
	}
}
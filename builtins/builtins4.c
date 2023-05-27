/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:24:53 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/05/27 12:46:35 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void    add_new_to_env(char *str, t_env **env)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (str[i] && str[i] != '=')
		i++;

	printf("%d %d\n", i, len);
	if (str[i] != '=')
		ft_lstadd_back_env(env, ft_lstnew_env(ft_strdup(str), NULL));
	else
		ft_lstadd_back_env(env, ft_lstnew_env(ft_strdup(ft_substr(str, 0, i))
			, ft_strdup(str + i + 1)));
	
}
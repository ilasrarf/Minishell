/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_norm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 23:59:50 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/06/22 00:04:53 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_expande(char **env, char *var, int len)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (my_strcmp(env[i], var))
		{
			free(var);
			return (ft_strdup(env[i] + len + 1));
		}
		i++;
	}
	free(var);
	return (ft_strdup(""));
}
void ft_dup_built(int fd[2])
{
    if (fd[1] > 2)
        dup2(fd[1], STDOUT_FILENO);
    if (fd[0] > 2)
        dup2(fd[0], STDIN_FILENO);
}
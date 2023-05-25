/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:39:09 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/05/08 12:00:51 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_handel_env(t_env **env)
{
    t_env *tmp1;

    tmp1 = *env;
    while ((*env))
    {
        printf("%s=", (*env)->name);
        printf("%s\n", (*env)->value);
        (*env) = (*env)->next;
    }
    *env = tmp1;
}

void	ft_handel_pwd(t_env **env)
{
    t_env   *tmp1;
    char    cur[1024];

    tmp1 = *env;
    getcwd(cur, sizeof(cur));
    if (cur[0])
    {
        printf("%s\n", cur);
    }
    else
    {
        while ((*env))
        {
            if (ft_strncmp((*env)->name, "PWD", 3) == 0)
            {
                printf("%s\n", (*env)->value);
                *env = tmp1;
            }
            (*env) = (*env)->next;
        }
        *env = tmp1;
    }
}
// void	ft_handel_exit(t_env **env)
// {
    
// }
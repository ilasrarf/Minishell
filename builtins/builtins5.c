/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:56:14 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/05/28 19:56:17 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_handel_unset(t_parser **prs,  t_env **env)
{
    t_env *tmp;
    t_env *h1;
    t_env *h2;
    int i;

    i = 0;
    if (!(*prs)->args[1])
        return ;
    tmp = (*env);
    if (ft_strcmp((*env)->name, (*prs)->args[i]))
    {
        
    }
    while ((*env)->next)
    {
        if (!ft_strcmp((*env)->next->name, (*prs)->args[i]))
        {
            h1 = (*env);
            h2 = (*env)->next
        }
        (*env) = (*env)->next;
    }
    
}

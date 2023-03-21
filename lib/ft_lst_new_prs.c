/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_new_prs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 20:47:57 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/03/20 21:38:23 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parser	*ft_lst_new_prs(char **str)
{
    t_parser *n1;
    
    n1 = malloc(sizeof(t_parser));
	if (n1)
        n1->args = str;
	return (n1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_new_prs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 20:47:57 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/03/23 23:43:06 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parser	*ft_lst_new_prs(char **str, char *in , char *out, int *fd)
{
    t_parser *n1;
    
    n1 = malloc(sizeof(t_parser));
	if (n1)
    {
        n1->args = str;
        n1->in_red = in;
        n1->out_red = out;
        n1->fd = fd;
        n1->next = NULL;
    }
	return (n1);
}

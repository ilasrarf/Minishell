/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_new_prs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 20:47:57 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/05/03 15:23:10 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parser	*ft_lst_new_prs(char **str, int in, int out)
{
	t_parser	*n1;

	n1 = malloc(sizeof(t_parser));
	if (n1)
	{
		n1->args = str;
		n1->in_red = in;
		n1->out_red = out;
		n1->next = NULL;
	}
	return (n1);
}

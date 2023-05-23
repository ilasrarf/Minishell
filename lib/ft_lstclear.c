/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 22:41:36 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/05/06 11:01:20 by aen-naas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstclear(t_parser **lst)
{
	t_parser	*temp;

	if (!lst || !*lst)
		return ;
	temp = *lst;
	while (temp)
	{
		temp = temp->next;
		ft_lstdelone(*lst);
		*lst = temp;
	}
}

void	ft_lstclear_lex(t_lexer **lst)
{
	if (!lst || !*lst)
		return ;
	while ((*lst))
	{
		ft_lstdelone_lex(*lst);
		(*lst) = (*lst)->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 22:41:36 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/03/22 00:40:58 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstclear(t_parser **lst)
{
	t_parser	*temp;
	// t_parser	*temp1;

	if (!lst || !*lst)
		return ;
	temp = *lst;
	// temp1 = *lst;
	while (temp)
	{
		temp = temp->next;
		ft_lstdelone(*lst);
		*lst = temp;
	}
	// temp1 = NULL;
}
void	ft_lstclear_lex(t_lexer **lst)
{
	// t_lexer	*temp;
	// t_lexer	*temp1;

	if (!lst || !*lst)
		return ;
	// temp = *lst;
	// temp1 = *lst;
	while ((*lst))
	{
		ft_lstdelone_lex(*lst);
		(*lst) = (*lst)->next;
		// *lst = temp;
	}
	// temp1 = NULL;
}
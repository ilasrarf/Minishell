/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 22:31:09 by ilasrarf          #+#    #+#             */
/*   Updated: 2023/05/28 19:53:12 by ilasrarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstdelone(t_parser *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return ;
	while (lst->args && lst->args[i])
	{
		free(lst->args[i]);
		i++;
	}
	if (lst->args)
		free(lst->args);
	free(lst);
}

void	ft_lstdelone_lex(t_lexer *lst)
{
	if (!lst)
		return ;
	free(lst->word);
	free(lst);
}

void	ft_lstdelone_env(t_env *lst)
{
	if (!lst)
		return ;
	free(lst->name);
	free(lst->value);
	free(lst);
}
